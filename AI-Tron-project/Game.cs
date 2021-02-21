using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;

namespace AI_Tron
{
    class Game
    {
        // AI当前头部位置
        private Point AI1_Head, AI2_Head;
        // 5个地图结点枚举，分别是 AI1、AI2的body && head，以及 NONE
        public enum NodeType { NODE_NONE, NODE_AI1_BODY, NODE_AI2_BODY, NODE_AI1_HEAD, NODE_AI2_HEAD };
        // 地图数组
        public NodeType[,] map;
        // 地图宽度，地图为正方形因此只有一个宽度
        public int mapWidth;
        // AI的类型
        public enum AIType { AI1, AI2 };
        // AI方向 枚举
        public enum DirectType { Direct_Up, Direct_Down, Direct_Left, Direct_Right, Direct_None };
        public DirectType AI1_direction, AI2_direction;

        // 初始化地图数据
        public void InitGame()
        {
            // 初始化map
            map = new NodeType[mapWidth, mapWidth];
            for (int i = 0; i < mapWidth; i++)
                for (int j = 0; j < mapWidth; j++)
                    map[i, j] = NodeType.NODE_NONE;
            // 保存头部
            AI1_Head = new Point(0, mapWidth / 2);
            AI2_Head = new Point(mapWidth - 1, mapWidth / 2);
            // 设置地图
            map[AI1_Head.X, AI1_Head.Y] = NodeType.NODE_AI1_HEAD;
            map[AI2_Head.X, AI2_Head.Y] = NodeType.NODE_AI2_HEAD;
        }
        // 游戏单步一次后可能的结果
        public enum StepResult { SR_AI1, SR_AI2, SR_NONE, SR_TIE };
        /*
         * @brief: 单步走一步
         * @return:
         *      SR_NONE     暂未分出胜负
         *      SR_AI1      AI1 获胜
         *      SR_AI2      AI2 获胜
         *      SR_TIE      平局
         */
        public StepResult TakeStep()
        {
            // 将地图中的head结点修改成body结点，并更新head
            map[AI1_Head.X, AI1_Head.Y] = NodeType.NODE_AI1_BODY;
            map[AI2_Head.X, AI2_Head.Y] = NodeType.NODE_AI2_BODY;
            // 头部移动一步
            switch (AI1_direction)
            {
                case DirectType.Direct_Up: AI1_Head.Y--; break;
                case DirectType.Direct_Down: AI1_Head.Y++; break;
                case DirectType.Direct_Left: AI1_Head.X--; break;
                case DirectType.Direct_Right: AI1_Head.X++; break;
            }
            switch (AI2_direction)
            {
                case DirectType.Direct_Up: AI2_Head.Y--; break;
                case DirectType.Direct_Down: AI2_Head.Y++; break;
                case DirectType.Direct_Left: AI2_Head.X--; break;
                case DirectType.Direct_Right: AI2_Head.X++; break;
            }

            // 判断新的AI head是否越界或碰撞
            bool AI1_fail = false, AI2_fail = false;
            if (AI1_Head.X < 0 || mapWidth <= AI1_Head.X
                || AI1_Head.Y < 0 || mapWidth <= AI1_Head.Y
                || map[AI1_Head.X, AI1_Head.Y] != NodeType.NODE_NONE)
                AI1_fail = true;
            if (AI2_Head.X < 0 || mapWidth <= AI2_Head.X
                || AI2_Head.Y < 0 || mapWidth <= AI2_Head.Y
                || map[AI2_Head.X, AI2_Head.Y] != NodeType.NODE_NONE)
                AI2_fail = true;
            // 特殊情况判断，两头相撞
            if (AI1_Head == AI2_Head)
                AI1_fail = AI2_fail = true;
            // 判断是否存在失败者
            if (AI1_fail && !AI2_fail)
                return StepResult.SR_AI2;
            else if (!AI1_fail && AI2_fail)
                return StepResult.SR_AI1;
            else if (AI1_fail && AI2_fail)
                return StepResult.SR_TIE;
            else
            {
                // 更新地图的head
                map[AI1_Head.X, AI1_Head.Y] = NodeType.NODE_AI1_HEAD;
                map[AI2_Head.X, AI2_Head.Y] = NodeType.NODE_AI2_HEAD;
                return StepResult.SR_NONE;
            }
        }
    }
}
