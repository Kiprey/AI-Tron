using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Threading;
using System.IO;

namespace AI_Tron
{
    // Controller 类用于游戏的整体流程，包括但不限于建立新线程、启动AI进程等。
    class Controller
    {
        // 游戏规则判定相关
        public Game game;
        // 开始游戏后的工作线程
        private Thread startingGameThread;
        // AI程序的文件路径
        public string AI1Path, AI2Path;
        // 单步最大/最小等待时间
        public int minWaitTime, maxSingleCostTime;
        // 与UI相关的函数委托。这些委托必须使用BeginInvoke调用
        public delegate void UIDelegate();
        private UIDelegate AI1Win_UpdateUI, AI2Win_UpdateUI, NoWiner_UpdateUI, drawUI;
        public delegate void errorNotifyDelegate(string str);
        private errorNotifyDelegate errorNotify, errorNotifyAndStopGame;
        // log 输出的文件名
        private string AI1LogFileName = Game.AIType.AI1.ToString() + "-log.txt";
        private string AI2LogFileName = Game.AIType.AI2.ToString() + "-log.txt";

        // 为 Controller 设置UI线程（主线程）的函数委托
        public void SetFunctionDelegate(UIDelegate AI1Win, UIDelegate AI2Win,
                UIDelegate NoWiner, UIDelegate draw, errorNotifyDelegate error, errorNotifyDelegate errorAbort)
        {
            AI1Win_UpdateUI = AI1Win;
            AI2Win_UpdateUI = AI2Win;
            NoWiner_UpdateUI = NoWiner;
            drawUI = draw;
            errorNotify = error;
            errorNotifyAndStopGame = errorAbort;
        }
        // 强制关闭某个AI进程，该函数将被Timer调用
        private void killAIProcess(object obj)
        {
            Process proc = (Process)obj;
            try
            {
                if (!proc.HasExited)
                    // 这里不能用 Close，必须用Kill下猛料
                    proc.Kill();
            }catch(Exception)
            {
                // 关闭 Process 时有时会触发竞争条件，即关闭一个已经关闭了的 Process
                // 这里的异常无需处理
            }
        }
        // 通过调用AI程序来获取目标方向
        // 注意该函数所在的线程将不会被强制终止，因为是异步委托调用
        private Game.DirectType GetAIMove(Game.AIType obj)
        {
            Game.AIType AIType = (Game.AIType)obj;
            Process proc = new Process();
            //关闭Shell的使用
            proc.StartInfo.UseShellExecute = false;
            //重定向标准输入
            proc.StartInfo.RedirectStandardInput = true;
            //重定向标准输出
            proc.StartInfo.RedirectStandardOutput = true;
            //重定向错误输出
            proc.StartInfo.RedirectStandardError = true;
            //设置不显示窗口
            proc.StartInfo.CreateNoWindow = true;
            //设定程序路径
            proc.StartInfo.FileName = AIType == Game.AIType.AI1 ? AI1Path : AI2Path;

            // 启动程序
            try
            {
                proc.Start();
            }
            catch (Exception e)
            {
                // 如果 AI 进程启动异常，则输出错误信息并停止游戏
                errorNotifyAndStopGame.BeginInvoke(AIType.ToString() + "程序执行出错！\n" +
                    "错误信息：" + e.Message,
                    null, null);
            }
            string inputStr;
            // 设置当前 AI 角色，是 AI1 还是 AI2 
            inputStr = AIType.ToString() + " \n";
            // 获取棋盘信息
            inputStr += game.mapWidth.ToString() + " \t" + game.mapWidth.ToString() + " \n";
            for (int i = 0; i < game.mapWidth; i++)
            {
                for (int j = 0; j < game.mapWidth; j++)
                {
                    switch (game.map[j, i])
                    {
                        case Game.NodeType.NODE_AI1_BODY: inputStr += "1B"; break;
                        case Game.NodeType.NODE_AI2_BODY: inputStr += "2B"; break;
                        case Game.NodeType.NODE_AI1_HEAD: inputStr += "1H"; break;
                        case Game.NodeType.NODE_AI2_HEAD: inputStr += "2H"; break;
                        case Game.NodeType.NODE_NONE: inputStr += "N"; break;
                    }
                    inputStr += " \t";
                }
                inputStr += " \n";
            }
            // 将当前棋盘信息写入AI进程中
            proc.StandardInput.WriteLine(inputStr);
            // 使用 timer 让进程在超时时强制关闭
            Timer timer = new Timer(
                new TimerCallback(killAIProcess), 
                proc, 
                maxSingleCostTime, 
                Timeout.Infinite);
            // 读取来自AI进程的数据
            string procOutputStr = proc.StandardOutput.ReadToEnd().Trim();
            string procErrorStr = proc.StandardError.ReadToEnd().Trim();
            // 如果AI进程传来了"错误信息"
            if (procErrorStr != "")
            {
                // 切割信息
                string[] strs = procErrorStr.Split('\n');
                // 遍历每一行
                foreach(string str in strs)
                    // 如果这个错误信息不是用户调试用的信息
                    if(!(procErrorStr.Length > 8 && procErrorStr.StartsWith("[DEBUG] ")))
                        // 则将其输出至UI中。
                        errorNotify.BeginInvoke(AIType.ToString() + "程序信息：" + procErrorStr, null, null);
            }
                
            // 将当前对局信息 以及 Error Msg 追加写入本地文件中，方便用户调试
            FileStream fs = new FileStream(AIType.ToString() + "-log.txt", FileMode.Append);
            StreamWriter wr = new StreamWriter(fs);
            wr.WriteLine(inputStr + procErrorStr);
            wr.Close();
            // 开始处理返回的字符串
            switch (procOutputStr)
            {
                case "up":
                    proc.Close();
                    return Game.DirectType.Direct_Up;
                case "down":
                    proc.Close();
                    return Game.DirectType.Direct_Down;
                case "left":
                    proc.Close();
                    return Game.DirectType.Direct_Left;
                case "right":
                    proc.Close();
                    return Game.DirectType.Direct_Right;
                case "none":
                    proc.Close();
                    return Game.DirectType.Direct_None;
                default:
                    if (procOutputStr == "")
                        errorNotify.BeginInvoke(AIType.ToString() + "程序执行超时 / 程序异常退出", null, null);
                    else
                        errorNotify.BeginInvoke(AIType.ToString() + "程序返回了无法识别的指令", null, null);
                    proc.Close();
                    return Game.DirectType.Direct_None;
            }
        }

        // 游戏开始前的初始化，即清空游戏棋盘、更新UI
        public void InitGame(int mapWidth)
        {
            game = new Game();
            game.mapWidth = mapWidth;
            game.InitGame();
            drawUI();

            // 清空原先的对局信息
            try
            {
                if (System.IO.File.Exists(AI1LogFileName))
                    System.IO.File.Delete(AI1LogFileName);
                if (System.IO.File.Exists(AI2LogFileName))
                    System.IO.File.Delete(AI2LogFileName);
            }
            catch(Exception e)
            {
                errorNotify.BeginInvoke("删除历史对局信息失败! 错误信息：" + e.Message, null, null);
            }
        }
        // 继续游戏，启动新线程
        public void StartGame()
        {
            // 设置新线程并启动
            startingGameThread = new Thread(ProcessGame);
            startingGameThread.Start();
        }
        // 暂停游戏，关闭游戏线程
        public void StopGame()
        {
            // 终止游戏线程
            if (startingGameThread.IsAlive)
                startingGameThread.Abort();
        }
        // 终止某个AI线程
        private void AIThreadAbort(object obj)
        {
            // 获取待关闭的 AI 线程
            Thread abortingAIThread = (Thread)obj;
            if (abortingAIThread.IsAlive)
                abortingAIThread.Abort();
        }
        // 获取AI程序下一个方向的函数委托
        delegate Game.DirectType AIMoveDelegate(Game.AIType ai);
        private void ProcessGame()
        {
            while(true)
            {
                // 使用异步委托获取方向
                try
                {
                    // 获取AI1 和 AI2 的移动方向
                    AIMoveDelegate AIDel = new AIMoveDelegate(GetAIMove);
                    IAsyncResult AsyncResult1 = AIDel.BeginInvoke(Game.AIType.AI1, null, null);
                    IAsyncResult AsyncResult2 = AIDel.BeginInvoke(Game.AIType.AI2, null, null);
                    Thread.Sleep(minWaitTime);
                    // 等待两个异步线程完成
                    AsyncResult1.AsyncWaitHandle.WaitOne();
                    AsyncResult2.AsyncWaitHandle.WaitOne();
                    // 获取返回值
                    Game.DirectType retDirect1 = AIDel.EndInvoke(AsyncResult1);
                    Game.DirectType retDirect2 = AIDel.EndInvoke(AsyncResult2);
                    // 对于那些异常退出的AI进程，保留上一次的方向
                    if (retDirect1 != Game.DirectType.Direct_None)
                        game.AI1_direction = retDirect1;
                    if (retDirect2 != Game.DirectType.Direct_None)
                        game.AI2_direction = retDirect2;
                }
                // 如果当前线程被终止
                catch(System.Threading.ThreadAbortException)
                {
                    // 不用做任何事情，因为GetAIMove内置的计时器会帮助kill AI process
                }
                catch (Exception)
                {
                    // 如果存在其他异常（这里主要指的是AI process 中的异常），则直接终止当前线程
                    errorNotifyAndStopGame.BeginInvoke("游戏线程已终止", null, null);
                    return;
                }

                // 行走一步
                Game.StepResult stepResult = game.TakeStep();
                // 处理这一步的结果
                switch (stepResult)
                {
                    // 如果这一步没有产生胜利者，则只更新UI即可，继续当前的工作线程
                    case Game.StepResult.SR_NONE: drawUI(); break;
                    // 如果产生了胜利者，则调用相应的UI更新程序结束游戏，并退出当前工作线程
                    case Game.StepResult.SR_AI1: AI1Win_UpdateUI.BeginInvoke(null, null); return;
                    case Game.StepResult.SR_AI2: AI2Win_UpdateUI.BeginInvoke(null, null); return;
                    case Game.StepResult.SR_TIE: NoWiner_UpdateUI.BeginInvoke(null, null); return;
                    // 对于异常情况，输出相关信息并停止游戏
                    default: errorNotifyAndStopGame.BeginInvoke("判断对局胜负失败", null, null); return;
                }
            }
        }
    }
}