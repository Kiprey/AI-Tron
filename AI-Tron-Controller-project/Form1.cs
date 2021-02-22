using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Windows.Forms;

namespace AI_Tron
{
    public partial class MainForm : Form
    {
        // 主控制器
        private Controller controller;
        // 游戏画布
        private Graphics gameGraph;
        // 标识游戏画布上结点的颜色
        private Color AI1_Color, AI2_Color, NoneNode_Color;

        public MainForm()
        {
            InitializeComponent();
        }
        // 选择AI1的文件路径
        private void GetFile1Button_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Windows可执行文件|*.exe";
            if (openFileDialog.ShowDialog() == DialogResult.OK)
                FilePath1.Text = openFileDialog.FileName;
        }
        // 选择AI2的文件路径
        private void GetFile2Button_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Windows可执行文件|*.exe";
            if (openFileDialog.ShowDialog() == DialogResult.OK)
                FilePath2.Text = openFileDialog.FileName;
        }
        // 游戏开始时，禁用一些box，以防在使用设置时被更改
        private void DisableBoxesWhenGameStart()
        {
            AI1groupBox.Enabled = false;
            AI2groupBox.Enabled = false;
            SettingsGroupBox.Enabled = false;
        }
        // 游戏结束时，启动一些box
        private void EnableBoxesWhenGameStop()
        {
            AI1groupBox.Enabled = true;
            AI2groupBox.Enabled = true;
            SettingsGroupBox.Enabled = true;
        }
        // 在RichTextBox中输出红色警告字符串
        // 该函数（应该？）是线程安全的
        private void NotifyError(string msg)
        {
            // 互斥锁
            lock(TextBox)
            {
                // 使用红色字体
                TextBox.SelectionColor = Color.Red;
                Log(msg);
                // 重新使用黑色字体
                TextBox.SelectionColor = Color.Black;
            }
        }
        // 设置错误信息后，停止当前游戏
        private void NotifyErrorAndStopGame(string msg)
        {
            NotifyError(msg);
            ResetButton();
            controller.StopGame();
        }
        private void MainForm_Load(object sender, EventArgs e)
        {
            controller = new Controller();
            controller.SetFunctionDelegate(
                new Controller.UIDelegate(AI1Win),
                new Controller.UIDelegate(AI2Win),
                new Controller.UIDelegate(noWiner),
                new Controller.UIDelegate(PaintMap),
                new Controller.errorNotifyDelegate(NotifyError),
                new Controller.errorNotifyDelegate(NotifyErrorAndStopGame)
            );
            // 重置按钮
            ResetButton();
            // 设置画布
            gameGraph = GameGroupBox.CreateGraphics();
            // 设置颜色
            AI1_Color = Color.Red;
            AI2_Color = Color.Blue;
            NoneNode_Color = Color.Silver;

            // 设置 FilePath 的颜色
            FilePath1.ForeColor = AI1_Color;
            FilePath2.ForeColor = AI2_Color;

            GameGroupBox.BackColor = NoneNode_Color;
        }
        // 输出信息至RichTextBox。这只是一个简单的Wrapper包装函数
        private void Log(string msg)
        {
            TextBox.AppendText(msg + "\n");
        }
        /*
         两个按钮可能的显示情况如下：其中 `!` 代表某个按钮被禁用
            初始：            开始游戏 !停止游戏
            游戏进行中：      暂停游戏 停止游戏
            游戏暂停中：      继续游戏 停止游戏
         */
        private void StartOrPauseGameButton_Click(object sender, EventArgs e)
        {
            if (StartOrPauseGameButton.Text == "暂停游戏")
            {
                controller.StopGame();
                Log("游戏已暂停");
                StartOrPauseGameButton.Text = "继续游戏";
            }
            else
            {
                if (StartOrPauseGameButton.Text == "开始游戏")
                {
                    // 准备开始游戏
                    controller.maxSingleCostTime = decimal.ToInt32(maxCostTimeNumeric.Value);
                    controller.minWaitTime = decimal.ToInt32(minCostTimeNumeric.Value);
                    // 判断 minTime 是否 大于 maxTime
                    if (controller.minWaitTime > controller.maxSingleCostTime)
                    {
                        MessageBox.Show("`单步最小间隔时间` 不得大于 `单步最多等待时间` ！", "警告！");
                        return;
                    }
                    StopGameButton.Enabled = true;
                    // 初始化Game类型实例，每次开始新游戏时一定要初始化一次
                    controller.InitGame(int.Parse(ReignWidthComboBox.Text));
                    controller.AI1Path = FilePath1.Text;
                    controller.AI2Path = FilePath2.Text;
                    // 开始新游戏后，清空TextBox
                    TextBox.Clear();
                }
                controller.StartGame();
                Log("游戏进行中...");
                StartOrPauseGameButton.Text = "暂停游戏";
            }
            DisableBoxesWhenGameStart();
        }

        private void StopGameButton_Click(object sender, EventArgs e)
        {
            ResetButton();
            Log("游戏已停止");
            controller.StopGame();
        }

        public void ResetButton()
        {
            // 重置按钮文本，以及当前按钮状态
            StartOrPauseGameButton.Text = "开始游戏";
            StopGameButton.Enabled = false;
            EnableBoxesWhenGameStop();
        }

        // 画图
        public void PaintMap()
        {
            // 获取map相关信息
            Game.NodeType[,] map = controller.game.map;
            int mapWidth = controller.game.mapWidth;

            Size carvasSize = GameGroupBox.Size;
            Size pointSize = new Size(carvasSize.Width / mapWidth, carvasSize.Height / mapWidth);
            int penWidth = 2;

            // 建立一个新画布，防止闪烁
            Bitmap bufferimage = new Bitmap(carvasSize.Width, carvasSize.Height);
            Graphics graph = Graphics.FromImage(bufferimage);

            // 清空画布
            graph.Clear(NoneNode_Color);
            graph.SmoothingMode = SmoothingMode.HighQuality; //高质量
            graph.PixelOffsetMode = PixelOffsetMode.HighQuality; //高像素偏移质量

            for (int i = 0; i < mapWidth; i++)
            {
                for (int j = 0; j < mapWidth; j++)
                {
                    Rectangle targetPoint = new Rectangle(
                        pointSize.Width * i, pointSize.Height * j,
                        pointSize.Width, pointSize.Height);
                    switch (map[i, j])
                    {
                        case Game.NodeType.NODE_AI1_BODY:
                            graph.FillEllipse(new SolidBrush(AI1_Color), targetPoint);
                            break;
                        case Game.NodeType.NODE_AI1_HEAD:
                            graph.DrawEllipse(new Pen(AI1_Color, penWidth), targetPoint);
                            break;
                        case Game.NodeType.NODE_AI2_BODY:
                            graph.FillEllipse(new SolidBrush(AI2_Color), targetPoint);
                            break;
                        case Game.NodeType.NODE_AI2_HEAD:
                            graph.DrawEllipse(new Pen(AI2_Color, penWidth), targetPoint);
                            break;
                        default: /* 空NODE无需draw */ break;
                    }
                }
            }
            // 画好后，画至控件上的Graphics
            gameGraph.DrawImage(bufferimage, 0, 0);
        }
        // 处理AI胜利的三个 UI 更新函数
        public void AI1Win()
        {
            ResetButton();
            Log("AI1 获胜！");
        }

        public void AI2Win()
        {
            ResetButton();
            Log("AI2 获胜！");
        }
        public void noWiner()
        {
            ResetButton();
            Log("平局！");
        }
    }
}