namespace AI_Tron
{
    partial class MainForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.panel2 = new System.Windows.Forms.Panel();
            this.SettingsGroupBox = new System.Windows.Forms.GroupBox();
            this.maxCostTimeNumeric = new System.Windows.Forms.NumericUpDown();
            this.label16 = new System.Windows.Forms.Label();
            this.minCostTimeNumeric = new System.Windows.Forms.NumericUpDown();
            this.label15 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.ReignWidthComboBox = new System.Windows.Forms.ComboBox();
            this.StopGameButton = new System.Windows.Forms.Button();
            this.AI2groupBox = new System.Windows.Forms.GroupBox();
            this.GetFile2Button = new System.Windows.Forms.Button();
            this.FilePath2 = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.AI1groupBox = new System.Windows.Forms.GroupBox();
            this.GetFile1Button = new System.Windows.Forms.Button();
            this.FilePath1 = new System.Windows.Forms.Label();
            this.StartOrPauseGameButton = new System.Windows.Forms.Button();
            this.GameGroupBox = new System.Windows.Forms.GroupBox();
            this.TextBox = new System.Windows.Forms.RichTextBox();
            this.panel2.SuspendLayout();
            this.SettingsGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.maxCostTimeNumeric)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.minCostTimeNumeric)).BeginInit();
            this.AI2groupBox.SuspendLayout();
            this.AI1groupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.TextBox);
            this.panel2.Controls.Add(this.SettingsGroupBox);
            this.panel2.Controls.Add(this.StopGameButton);
            this.panel2.Controls.Add(this.AI2groupBox);
            this.panel2.Controls.Add(this.label17);
            this.panel2.Controls.Add(this.AI1groupBox);
            this.panel2.Controls.Add(this.StartOrPauseGameButton);
            this.panel2.Location = new System.Drawing.Point(618, 12);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(400, 600);
            this.panel2.TabIndex = 1;
            // 
            // SettingsGroupBox
            // 
            this.SettingsGroupBox.Controls.Add(this.maxCostTimeNumeric);
            this.SettingsGroupBox.Controls.Add(this.label16);
            this.SettingsGroupBox.Controls.Add(this.minCostTimeNumeric);
            this.SettingsGroupBox.Controls.Add(this.label15);
            this.SettingsGroupBox.Controls.Add(this.label11);
            this.SettingsGroupBox.Controls.Add(this.ReignWidthComboBox);
            this.SettingsGroupBox.Location = new System.Drawing.Point(3, 460);
            this.SettingsGroupBox.Name = "SettingsGroupBox";
            this.SettingsGroupBox.Size = new System.Drawing.Size(397, 135);
            this.SettingsGroupBox.TabIndex = 2;
            this.SettingsGroupBox.TabStop = false;
            this.SettingsGroupBox.Text = "设置";
            // 
            // maxCostTimeNumeric
            // 
            this.maxCostTimeNumeric.Location = new System.Drawing.Point(238, 92);
            this.maxCostTimeNumeric.Maximum = new decimal(new int[] {
            100000,
            0,
            0,
            0});
            this.maxCostTimeNumeric.Name = "maxCostTimeNumeric";
            this.maxCostTimeNumeric.Size = new System.Drawing.Size(120, 25);
            this.maxCostTimeNumeric.TabIndex = 15;
            this.maxCostTimeNumeric.Value = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(9, 92);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(188, 15);
            this.label16.TabIndex = 14;
            this.label16.Text = "单步最多等待时间（ms）：";
            // 
            // minCostTimeNumeric
            // 
            this.minCostTimeNumeric.Location = new System.Drawing.Point(236, 54);
            this.minCostTimeNumeric.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.minCostTimeNumeric.Name = "minCostTimeNumeric";
            this.minCostTimeNumeric.Size = new System.Drawing.Size(120, 25);
            this.minCostTimeNumeric.TabIndex = 13;
            this.minCostTimeNumeric.Value = new decimal(new int[] {
            200,
            0,
            0,
            0});
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(8, 56);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(188, 15);
            this.label15.TabIndex = 12;
            this.label15.Text = "单步最少间隔时间（ms）：";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(6, 26);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(157, 15);
            this.label11.TabIndex = 4;
            this.label11.Text = "游戏区域边长（格）：";
            // 
            // ReignWidthComboBox
            // 
            this.ReignWidthComboBox.FormattingEnabled = true;
            this.ReignWidthComboBox.Items.AddRange(new object[] {
            "10",
            "15",
            "20",
            "25",
            "30",
            "40"});
            this.ReignWidthComboBox.Location = new System.Drawing.Point(236, 23);
            this.ReignWidthComboBox.Name = "ReignWidthComboBox";
            this.ReignWidthComboBox.Size = new System.Drawing.Size(57, 23);
            this.ReignWidthComboBox.TabIndex = 0;
            this.ReignWidthComboBox.Text = "30";
            // 
            // StopGameButton
            // 
            this.StopGameButton.Location = new System.Drawing.Point(275, 131);
            this.StopGameButton.Name = "StopGameButton";
            this.StopGameButton.Size = new System.Drawing.Size(95, 39);
            this.StopGameButton.TabIndex = 7;
            this.StopGameButton.Text = "停止游戏";
            this.StopGameButton.UseVisualStyleBackColor = true;
            this.StopGameButton.Click += new System.EventHandler(this.StopGameButton_Click);
            // 
            // AI2groupBox
            // 
            this.AI2groupBox.Controls.Add(this.GetFile2Button);
            this.AI2groupBox.Controls.Add(this.FilePath2);
            this.AI2groupBox.Location = new System.Drawing.Point(3, 321);
            this.AI2groupBox.Name = "AI2groupBox";
            this.AI2groupBox.Size = new System.Drawing.Size(397, 133);
            this.AI2groupBox.TabIndex = 4;
            this.AI2groupBox.TabStop = false;
            this.AI2groupBox.Text = "AI_2";
            // 
            // GetFile2Button
            // 
            this.GetFile2Button.Location = new System.Drawing.Point(9, 82);
            this.GetFile2Button.Name = "GetFile2Button";
            this.GetFile2Button.Size = new System.Drawing.Size(109, 34);
            this.GetFile2Button.TabIndex = 5;
            this.GetFile2Button.Text = "选择AI文件";
            this.GetFile2Button.UseVisualStyleBackColor = true;
            this.GetFile2Button.Click += new System.EventHandler(this.GetFile2Button_Click);
            // 
            // FilePath2
            // 
            this.FilePath2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.FilePath2.Font = new System.Drawing.Font("宋体", 12F);
            this.FilePath2.Location = new System.Drawing.Point(3, 21);
            this.FilePath2.Name = "FilePath2";
            this.FilePath2.Size = new System.Drawing.Size(391, 109);
            this.FilePath2.TabIndex = 2;
            this.FilePath2.Text = "<no path>";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Font = new System.Drawing.Font("宋体", 12F);
            this.label17.Location = new System.Drawing.Point(15, 9);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(109, 20);
            this.label17.TabIndex = 6;
            this.label17.Text = "游戏信息：";
            // 
            // AI1groupBox
            // 
            this.AI1groupBox.Controls.Add(this.GetFile1Button);
            this.AI1groupBox.Controls.Add(this.FilePath1);
            this.AI1groupBox.Location = new System.Drawing.Point(3, 176);
            this.AI1groupBox.Name = "AI1groupBox";
            this.AI1groupBox.Size = new System.Drawing.Size(397, 139);
            this.AI1groupBox.TabIndex = 0;
            this.AI1groupBox.TabStop = false;
            this.AI1groupBox.Text = "AI_1";
            // 
            // GetFile1Button
            // 
            this.GetFile1Button.Location = new System.Drawing.Point(9, 85);
            this.GetFile1Button.Name = "GetFile1Button";
            this.GetFile1Button.Size = new System.Drawing.Size(109, 34);
            this.GetFile1Button.TabIndex = 5;
            this.GetFile1Button.Text = "选择AI文件";
            this.GetFile1Button.UseVisualStyleBackColor = true;
            this.GetFile1Button.Click += new System.EventHandler(this.GetFile1Button_Click);
            // 
            // FilePath1
            // 
            this.FilePath1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.FilePath1.Font = new System.Drawing.Font("宋体", 12F);
            this.FilePath1.Location = new System.Drawing.Point(3, 21);
            this.FilePath1.Name = "FilePath1";
            this.FilePath1.Size = new System.Drawing.Size(391, 115);
            this.FilePath1.TabIndex = 2;
            this.FilePath1.Text = "<no path>";
            // 
            // StartOrPauseGameButton
            // 
            this.StartOrPauseGameButton.Location = new System.Drawing.Point(26, 131);
            this.StartOrPauseGameButton.Name = "StartOrPauseGameButton";
            this.StartOrPauseGameButton.Size = new System.Drawing.Size(95, 39);
            this.StartOrPauseGameButton.TabIndex = 4;
            this.StartOrPauseGameButton.Text = "开始游戏";
            this.StartOrPauseGameButton.UseVisualStyleBackColor = true;
            this.StartOrPauseGameButton.Click += new System.EventHandler(this.StartOrPauseGameButton_Click);
            // 
            // GameGroupBox
            // 
            this.GameGroupBox.Location = new System.Drawing.Point(12, 12);
            this.GameGroupBox.Name = "GameGroupBox";
            this.GameGroupBox.Size = new System.Drawing.Size(600, 600);
            this.GameGroupBox.TabIndex = 2;
            this.GameGroupBox.TabStop = false;
            this.GameGroupBox.Text = "游戏区域";
            // 
            // TextBox
            // 
            this.TextBox.Location = new System.Drawing.Point(26, 32);
            this.TextBox.Name = "TextBox";
            this.TextBox.Size = new System.Drawing.Size(344, 76);
            this.TextBox.TabIndex = 8;
            this.TextBox.Text = "";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(120F, 120F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.ClientSize = new System.Drawing.Size(1027, 619);
            this.Controls.Add(this.GameGroupBox);
            this.Controls.Add(this.panel2);
            this.MaximizeBox = false;
            this.Name = "MainForm";
            this.Text = "Tron-AI对战";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.SettingsGroupBox.ResumeLayout(false);
            this.SettingsGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.maxCostTimeNumeric)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.minCostTimeNumeric)).EndInit();
            this.AI2groupBox.ResumeLayout(false);
            this.AI1groupBox.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.GroupBox SettingsGroupBox;
        private System.Windows.Forms.GroupBox AI1groupBox;
        private System.Windows.Forms.Button GetFile1Button;
        private System.Windows.Forms.GroupBox AI2groupBox;
        private System.Windows.Forms.Button GetFile2Button;
        private System.Windows.Forms.ComboBox ReignWidthComboBox;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Button StartOrPauseGameButton;
        private System.Windows.Forms.NumericUpDown maxCostTimeNumeric;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.NumericUpDown minCostTimeNumeric;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Button StopGameButton;
        private System.Windows.Forms.GroupBox GameGroupBox;
        private System.Windows.Forms.Label FilePath2;
        private System.Windows.Forms.Label FilePath1;
        private System.Windows.Forms.RichTextBox TextBox;
    }
}

