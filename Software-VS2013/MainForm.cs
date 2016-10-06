// Motion Detection sample application
// AForge.NET Framework
// http://www.aforgenet.com/framework/
//
// Copyright ?AForge.NET, 2006-2012
// contacts@aforgenet.com
//

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.IO.Ports;
using System.Diagnostics; //stopwatch
using AForge;
using AForge.Imaging;
using AForge.Video;
using AForge.Video.VFW;
using AForge.Video.DirectShow;
using AForge.Vision.Motion;
using AForge.Imaging.Filters;

namespace RubikSolverSample
{
    public partial class MainForm : Form
    {
        // opened video source
        private IVideoSource videoSource = null;
        // motion detector
        MotionDetector detector = new MotionDetector(
            new TwoFramesDifferenceDetector(),
            new MotionAreaHighlighting());


        // statistics length
        private const int statLength = 15;
        // current statistics index
        private int statIndex = 0;
        // ready statistics values
        private int statReady = 0;
        // statistics array
        private int[] statCount = new int[statLength];

        // counter used for flashing
        private int flash = 0;
        bool All_Scan_OK;
        bool Button3Statue;
        private byte[] cube_status = new byte[48];

        int currentStatus = 0x00;
        const byte CUBE_GRAY = 0x00;
        const byte CUBE_WHITE = (byte)'D';
        const byte CUBE_YELLOW = (byte)'U';
        const byte CUBE_ORANGE = (byte)'L';
        const byte CUBE_RED =  (byte)'R';
        const byte CUBE_BLUE = (byte)'F';
        const byte CUBE_GREEN = (byte)'B';

        Stopwatch sw; //秒表对象
        TimeSpan ts;
        // Constructor
        public MainForm()
        {
            InitializeComponent();
            CheckForIllegalCrossThreadCalls = false;
            Application.Idle += new EventHandler(Application_Idle);
        }
        //initialize color display
        private void MainForm_Load(object sender, EventArgs e)
        {

            for (int i = 0; i < 48; i++)
            {
                cube_status[i] = 0x00;
            }
            SearchAndAddSerialToComboBox(serialPort1, comboBox1);

        }
        // Application's main form is closing
        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            CloseVideoSource();
        }

        // "Exit" menu item clicked
        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }



        // Open local video capture device
        private void localVideoCaptureDeviceToolStripMenuItem_Click(object sender, EventArgs e)
        {
            VideoCaptureDeviceForm form = new VideoCaptureDeviceForm();

            if (form.ShowDialog(this) == DialogResult.OK)
            {
                // create video source
                VideoCaptureDevice videoSource = new VideoCaptureDevice(form.VideoDevice);

                // open it
                OpenVideoSource(videoSource);
            }
        }



        // Open video source
        private void OpenVideoSource(IVideoSource source)
        {
            // set busy cursor
            this.Cursor = Cursors.WaitCursor;

            // close previous video source
            CloseVideoSource();

            // start new video source
            videoSourcePlayer.VideoSource = new AsyncVideoSource(source);
            videoSourcePlayer.Start();

            // reset statistics
            statIndex = statReady = 0;

            // start timers
            timer.Start();
            alarmTimer.Start();
            timer1.Start();
            videoSource = source;

            this.Cursor = Cursors.Default;
        }

        // Close current video source
        private void CloseVideoSource()
        {
            // set busy cursor
            this.Cursor = Cursors.WaitCursor;

            // stop current video source
            videoSourcePlayer.SignalToStop();

            // wait 2 seconds until camera stops
            for (int i = 0; (i < 50) && (videoSourcePlayer.IsRunning); i++)
            {
                Thread.Sleep(100);
            }
            if (videoSourcePlayer.IsRunning)
                videoSourcePlayer.Stop();

            // stop timers
            timer.Stop();
            alarmTimer.Stop();



            // reset motion detector
            if (detector != null)
                detector.Reset();

            videoSourcePlayer.BorderColor = Color.Black;
            this.Cursor = Cursors.Default;
        }
       
        private void drawCross(BitmapData bitmapData, Color color)
        {
            Drawing.Rectangle(bitmapData, new Rectangle(155, 50, 20, 20), color);
            Drawing.Rectangle(bitmapData, new Rectangle(210, 50, 20, 20), color);
            Drawing.Rectangle(bitmapData, new Rectangle(265, 50, 20, 20), color);
            Drawing.Rectangle(bitmapData, new Rectangle(155, 102, 20, 20), color);
            Drawing.Rectangle(bitmapData, new Rectangle(210, 102, 20, 20), color);
            Drawing.Rectangle(bitmapData, new Rectangle(265, 102, 20, 20), color);
            Drawing.Rectangle(bitmapData, new Rectangle(155, 152, 20, 20), color);
            Drawing.Rectangle(bitmapData, new Rectangle(210, 152, 20, 20), color);
            Drawing.Rectangle(bitmapData, new Rectangle(265, 152, 20, 20), color);
        }
        private void saveColorToCubeStatusTab(byte[] temp_status)
        {
            switch (temp_status[4])
            {
                case CUBE_BLUE:
                    cube_status[35] = temp_status[0];
                    cube_status[1] =  temp_status[1];
                    cube_status[25] = temp_status[2];
                    cube_status[18] = temp_status[3];
                    cube_status[16] = temp_status[5];
                    cube_status[40] = temp_status[6];
                    cube_status[9] =  temp_status[7];
                    cube_status[38] = temp_status[8];
                    WriteByteToSerialPort(0xA2);   
                    break;
                case CUBE_WHITE:
                    cube_status[39] = temp_status[0];
                    cube_status[8] = temp_status[1];
                    cube_status[36] = temp_status[2];
                    cube_status[14] = temp_status[3];
                    cube_status[10] = temp_status[5];
                    cube_status[42] = temp_status[6];
                    cube_status[12] = temp_status[7];
                    cube_status[45] = temp_status[8];
                    WriteByteToSerialPort(0xA3);    
                    break;
                case CUBE_GREEN:
                    cube_status[44] = temp_status[0];
                    cube_status[13] = temp_status[1];
                    cube_status[46] = temp_status[2];
                    cube_status[22] = temp_status[3];
                    cube_status[20] = temp_status[5];
                    cube_status[31] = temp_status[6];
                    cube_status[5] = temp_status[7];
                    cube_status[29] = temp_status[8];
                    WriteByteToSerialPort(0xA4);    
                    break;
                case CUBE_YELLOW:
                    cube_status[30] = temp_status[0];
                    cube_status[4] = temp_status[1];
                    cube_status[27] = temp_status[2];
                    cube_status[6] = temp_status[3];
                    cube_status[2] = temp_status[5];
                    cube_status[33] = temp_status[6];
                    cube_status[0] = temp_status[7];
                    cube_status[24] = temp_status[8];
                    WriteByteToSerialPort(0xA5);    
                    break;
                case CUBE_ORANGE:
                    cube_status[32] = temp_status[0];
                    cube_status[7] = temp_status[1];
                    cube_status[34] = temp_status[2];
                    cube_status[23] = temp_status[3];
                    cube_status[19] = temp_status[5];
                    cube_status[43] = temp_status[6];
                    cube_status[15] = temp_status[7];
                    cube_status[41] = temp_status[8];
                    WriteByteToSerialPort(0xA6); 
                    break;
                case CUBE_RED:
                    cube_status[26] = temp_status[0];
                    cube_status[3] = temp_status[1];
                    cube_status[28] = temp_status[2];
                    cube_status[17] = temp_status[3];
                    cube_status[21] = temp_status[5];
                    cube_status[37] = temp_status[6];
                    cube_status[11] = temp_status[7];
                    cube_status[47] = temp_status[8];
                    WriteByteToSerialPort(0xA7);
                    textBox1.Text += DateTime.Now.ToString("hh:mm:ss") + " Calculating......\r\n";
                    textBox1.SelectionStart = textBox1.Text.Length;
                    textBox1.ScrollToCaret();
                    All_Scan_OK = true;
                   
                    break;
            }
        }
        private byte identifyColor(byte R, byte G, byte B)
        {
            byte color;
            float hue;
            int RG, RB, BG;
            color = 0;
            hue = Color.FromArgb(R, G, B).GetHue();
            RG = (int)R - (int)G;
            RB = (int)R - (int)B;
            BG = (int)B - (int)G;

            
            //if (R < 170 && R > 130 && G < 170 && G > 130 && B < 170 && B > 130)
            if (Math.Abs(RG) < 30 && Math.Abs(RB) < 30 && Math.Abs(BG) < 30)
            {
                color = CUBE_WHITE;
            }
            else if (hue < 20 || hue > 300)
            {
                color = CUBE_RED;
            }
            else if (hue > 15 && hue < 40)
            {
                color = CUBE_ORANGE;
            }
            else if (hue >= 40 && hue <= 70)
            {
                color = CUBE_YELLOW;
            }
            else if (hue > 150 && hue < 170)
            {
                color = CUBE_GREEN;
            }
            else if (hue > 200 && hue < 300)
            {
                color = CUBE_BLUE;
            }
            return color;
        }
        // New frame received by the player
        private void videoSourcePlayer_NewFrame(object sender, ref Bitmap image)
        {
            lock (this)
            {
                Color green = Color.FromArgb(128, 0, 255, 0);
                Color Red = Color.FromArgb(128, 255, 0, 0);
                BitmapData bitmapData = image.LockBits(new Rectangle(0, 0, image.Width, image.Height),
                    ImageLockMode.ReadWrite, image.PixelFormat);

                drawCross(bitmapData, Red);
                byte[] watch = new byte[3];
                byte[] temp_status = new byte[9];
                bool ScanOK_flg = false;
                if (currentStatus == 0xA1 || currentStatus == 0xA2 || currentStatus == 0xA3 ||
                    currentStatus == 0xA4 || currentStatus == 0xA5 || currentStatus == 0xA6)
                {


                    
                   
                    unsafe
                    {
                        byte* pIn = (byte*)(bitmapData.Scan0.ToPointer());

                        for (int y = 0; y < bitmapData.Height; y++)
                        {
                            for (int x = 0; x < bitmapData.Width; x++)
                            {
                                //center

                                if (x == 165 && y == 60)
                                {
                                    watch[0] = pIn[0];
                                    watch[1] = pIn[1];
                                    watch[2] = pIn[2];
                                    temp_status[0] = identifyColor(pIn[2], pIn[1], pIn[0]);
                                }
                                else if (x == 220 && y == 60)
                                {
                                    watch[0] = pIn[0];
                                    watch[1] = pIn[1];
                                    watch[2] = pIn[2];
                                    temp_status[1] = identifyColor(pIn[2], pIn[1], pIn[0]);
                                }
                                else if (x == 275 && y == 60)
                                {
                                    watch[0] = pIn[0];
                                    watch[1] = pIn[1];
                                    watch[2] = pIn[2];
                                    temp_status[2] = identifyColor(pIn[2], pIn[1], pIn[0]);
                                }
                                else if (x == 165 && y == 112)
                                {
                                    watch[0] = pIn[0];
                                    watch[1] = pIn[1];
                                    watch[2] = pIn[2];
                                    temp_status[3] = identifyColor(pIn[2], pIn[1], pIn[0]);
                                }
                                else if (x == 220 && y == 112)
                                {
                                    watch[0] = pIn[0];
                                    watch[1] = pIn[1];
                                    watch[2] = pIn[2];
                                    temp_status[4] = identifyColor(pIn[2], pIn[1], pIn[0]);
                                }
                                else if (x == 275 && y == 112)
                                {
                                    watch[0] = pIn[0];
                                    watch[1] = pIn[1];
                                    watch[2] = pIn[2];
                                    temp_status[5] = identifyColor(pIn[2], pIn[1], pIn[0]);
                                }
                                else if (x == 165 && y == 160)
                                {
                                    watch[0] = pIn[0];
                                    watch[1] = pIn[1];
                                    watch[2] = pIn[2];
                                    temp_status[6] = identifyColor(pIn[2], pIn[1], pIn[0]);
                                }
                                else if (x == 220 && y == 160)
                                {
                                    watch[0] = pIn[0];
                                    watch[1] = pIn[1];
                                    watch[2] = pIn[2];
                                    temp_status[7] = identifyColor(pIn[2], pIn[1], pIn[0]);
                                }
                                else if (x == 275 && y == 160)
                                {
                                    watch[0] = pIn[0];
                                    watch[1] = pIn[1];
                                    watch[2] = pIn[2];
                                    temp_status[8] = identifyColor(pIn[2], pIn[1], pIn[0]);
                                }
                                if (currentStatus == 0xA1)
                                {
                                    temp_status[4] = CUBE_BLUE;
                                }
                                else if (currentStatus == 0xA2)
                                {
                                    temp_status[4] = CUBE_WHITE;
                                }
                                else if (currentStatus == 0xA3)
                                {
                                    temp_status[4] = CUBE_GREEN;
                                }
                                else if (currentStatus == 0xA4)
                                {
                                    temp_status[4] = CUBE_YELLOW;
                                }
                                else if (currentStatus == 0xA5)
                                {
                                    temp_status[4] = CUBE_ORANGE;
                                }
                                else if (currentStatus == 0xA6)
                                {
                                    temp_status[4] = CUBE_RED;
                                }
                                pIn += 3;

                            }
                            pIn += bitmapData.Stride - bitmapData.Width * 3;
                            
                        }
                    }
                    ScanOK_flg = true;
                    for (int t = 0; t < 9; t++)
                    {
                        if (temp_status[t] == 0)
                        {
                            ScanOK_flg = false;
                        }
                    }

                    if (ScanOK_flg)
                    {
                        saveColorToCubeStatusTab(temp_status);
                        currentStatus = 0x00;
                    }
                    
                }
                


                image.UnlockBits(bitmapData);

            }
        }


        // Update some UI elements
        private void Application_Idle(object sender, EventArgs e)
        {
            //objectsCountLabel.Text = ( detectedObjectsCount < 0 ) ? string.Empty : "Objects: " + detectedObjectsCount;
        }


        // On timer event - gather statistics
        private void timer_Tick(object sender, EventArgs e)
        {
            IVideoSource videoSource = videoSourcePlayer.VideoSource;

            if (videoSource != null)
            {
                // get number of frames for the last second
                statCount[statIndex] = videoSource.FramesReceived;

                // increment indexes
                if (++statIndex >= statLength)
                    statIndex = 0;
                if (statReady < statLength)
                    statReady++;

                float fps = 0;

                // calculate average value
                for (int i = 0; i < statReady; i++)
                {
                    fps += statCount[i];
                }
                fps /= statReady;

                statCount[statIndex] = 0;

                fpsLabel.Text = fps.ToString("F2") + " fps";
            }
        }



        // Timer used for flashing in the case if motion is detected
        private void alarmTimer_Tick(object sender, EventArgs e)
        {
            if (flash != 0)
            {
                videoSourcePlayer.BorderColor = (flash % 2 == 1) ? Color.Black : Color.Red;
                flash--;
            }
        }
        //
        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.FillRectangle(new SolidBrush(Color.Black), 0, 0, pictureBox1.Width, pictureBox1.Height);
        }
 


        private void SearchAndAddSerialToComboBox(SerialPort MyPort, ComboBox MyBox)
        {                                                               //将可用端口号添加到ComboBox
            string[] MyString = new string[20];                         //最多容纳20个，太多会影响调试效率
            string Buffer;                                              //缓存
            MyBox.Items.Clear();                                        //清空ComboBox内容
            for (int i = 1; i < 20; i++)                                //循环
            {
                try                                                     //核心原理是依靠try和catch完成遍历
                {
                    Buffer = "COM" + i.ToString();
                    MyPort.PortName = Buffer;
                    MyPort.Open();                                      //如果失败，后面的代码不会执行
                    MyString[i - 1] = Buffer;
                    MyBox.Items.Add(Buffer);                            //打开成功，添加至下俩列表
                    MyPort.Close();                                     //关闭
                }
                catch
                {

                }
            }
            MyBox.Text = MyString[0];                                   //初始化
        }

        private void button1_Click(object sender, EventArgs e)
        {
            SearchAndAddSerialToComboBox(serialPort1, comboBox1);       //扫描并讲课用串口添加至下拉列表
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)                                     //串口打开就关闭
            {
                try
                {
                    serialPort1.Close();
                }
                catch { }                                               //确保万无一失
                //button1.Text = "打开串口";
                button3.BackgroundImage = Properties.Resources.Image2;  //灭
                Button3Statue = false;                                  //按钮状态
            }
            else
            {
                try
                {
                    serialPort1.PortName = comboBox1.Text;              //端口号
                    serialPort1.Open();                                 //打开端口
                    //button1.Text = "关闭串口";
                    button3.BackgroundImage = Properties.Resources.Image1;//亮
                    Button3Statue = true;                                //按钮状态
                }
                catch
                {
                    MessageBox.Show("串口打开失败", "error");
                }
            }
        }

        private void WriteByteToSerialPort(byte data)                   //单字节写入串口
        {
            byte[] Buffer = new byte[2] { 0xFE, data };                       //定义数组
            if (serialPort1.IsOpen)                                     //传输数据的前提是端口已打开
            {
                try
                {
                    serialPort1.Write(Buffer, 0, 2);                    //写数据
                }
                catch
                {
                    MessageBox.Show("串口数据发送出错，请检查.", "error");//错误处理
                }
            }
        }
        bool frameHead = false; 
        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {

            byte data = (byte)serialPort1.ReadByte();

            data = data;
            if (frameHead)
            {
                frameHead = false;
                if (data == 0xA1)           //第一面转好了 the 
                {
                    
                    currentStatus = 0xA1;
                    textBox1.Text += DateTime.Now.ToString("hh:mm:ss") + " 开始识别第一面\r\n";    //Scanning the front surface
                    textBox1.SelectionStart = textBox1.Text.Length;
                    textBox1.ScrollToCaret();
                    //WriteByteToSerialPort(0xA2);    //开始识别第二面
                }
                else if (data == 0xA2)      //第二面转好了
                {
                    
                    currentStatus = 0xA2;
                    textBox1.Text += DateTime.Now.ToString("hh:mm:ss") + " 开始识别第二面\r\n";    //Scanning the TOP surface
                    textBox1.SelectionStart = textBox1.Text.Length;
                    textBox1.ScrollToCaret();
                    //WriteByteToSerialPort(0xA3);    //开始识别第三面
                }
                else if (data == 0xA3)
                {
                    currentStatus = 0xA3;
                    textBox1.Text += DateTime.Now.ToString("hh:mm:ss") + " 开始识别第三面\r\n";     //Scanning the Back surface
                    textBox1.SelectionStart = textBox1.Text.Length;
                    textBox1.ScrollToCaret();
                    //WriteByteToSerialPort(0xA4);    //开始识别第四面
                }
                else if (data == 0xA4)
                {
                    currentStatus = 0xA4;
                    textBox1.Text += DateTime.Now.ToString("hh:mm:ss") + " 开始识别第四面\r\n";
                    textBox1.SelectionStart = textBox1.Text.Length;
                    textBox1.ScrollToCaret();
                    //WriteByteToSerialPort(0xA5);    //开始识别第五面
                }
                else if (data == 0xA5)
                {
                    currentStatus = 0xA5;
                    textBox1.Text += DateTime.Now.ToString("hh:mm:ss") + " 开始识别第五面\r\n";
                    textBox1.SelectionStart = textBox1.Text.Length;
                    textBox1.ScrollToCaret();
                    //WriteByteToSerialPort(0xA6);    //开始识别第六面
                }
                else if (data == 0xA6)
                {
                    currentStatus = 0xA6;
                    textBox1.Text += DateTime.Now.ToString("hh:mm:ss") + " 开始识别第六面\r\n";
                    textBox1.SelectionStart = textBox1.Text.Length;
                    textBox1.ScrollToCaret();
                    //全部识别完成，开始算法
                }
                else if (data == 0xAA)
                {
                    sw.Stop();
                    timer2.Stop();
                }
                
              
            }
            if (data == 0xfe)
            {
                frameHead = true;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            WriteByteToSerialPort(0xA0);
        }

        //Start button
        private void button4_Click(object sender, EventArgs e)
        {
            WriteByteToSerialPort(0xA1);
            for (int t = 0; t < 48; t++)
            {
                cube_status[t] = 0;
            }
            sw = new Stopwatch();
 
            timer2.Interval = 1;
            sw.Start();
            timer2.Start();

           
        }

        private Brush getColorformStatus(int color)
        {
            if (color == CUBE_WHITE)
            {
                return new SolidBrush(Color.White);
            }
            else if (color == CUBE_BLUE)
            {
                return new SolidBrush(Color.Blue);
            }
            else if (color == CUBE_GREEN)
            {
                return new SolidBrush(Color.MediumSeaGreen);
            }
            else if (color == CUBE_ORANGE)
            {
                return new SolidBrush(Color.Orange);
            }
            else if (color == CUBE_YELLOW)
            {
                return new SolidBrush(Color.Yellow);
            }
            else if (color == CUBE_RED)
            {
                return new SolidBrush(Color.Maroon);
            }
            else 
            {
                return new SolidBrush(Color.Gray);
            }
        }
        //refresh picture every 500ms
        private void timer1_Tick(object sender, EventArgs e)
        {
            
            


            //temp_status
            Graphics g = Graphics.FromHwnd(this.pictureBox1.Handle);
            //背景色 
            //g.FillRectangle(getColorformStatus(1), 0, 0, 240, 180);
            g.FillRectangle(new SolidBrush(Color.Gray), 0, 0, 240, 180);
            //中心块颜色
            g.FillRectangle(new SolidBrush(Color.Yellow), 80, 20, 20, 20);
            g.FillRectangle(new SolidBrush(Color.Blue), 80, 80, 20, 20);
            g.FillRectangle(new SolidBrush(Color.White), 80, 140, 20, 20);
            g.FillRectangle(new SolidBrush(Color.Orange), 20, 80, 20, 20);
            g.FillRectangle(new SolidBrush(Color.Maroon), 140, 80, 20, 20);
            g.FillRectangle(new SolidBrush(Color.MediumSeaGreen), 200, 80, 20, 20);

            //黄色面
            g.FillRectangle(getColorformStatus(cube_status[30]), 60, 0, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[4]), 80, 0, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[27]), 100, 0, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[6]), 60, 20, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[2]), 100, 20, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[33]), 60, 40, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[0]), 80, 40, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[24]), 100, 40, 20, 20);
            //橙色面
            g.FillRectangle(getColorformStatus(cube_status[32]), 0, 60, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[7]), 20, 60, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[34]), 40, 60, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[23]), 0, 80, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[19]), 40, 80, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[43]), 0, 100, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[15]), 20, 100, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[41]), 40, 100, 20, 20);
            //白色面
            g.FillRectangle(getColorformStatus(cube_status[39]), 60, 120, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[8]), 80, 120, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[36]), 100, 120, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[14]), 60, 140, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[10]), 100, 140, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[42]), 60, 160, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[12]), 80, 160, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[45]), 100, 160, 20, 20);
            //红色面
            g.FillRectangle(getColorformStatus(cube_status[26]), 120, 60, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[3]), 140, 60, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[28]), 160, 60, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[17]), 120, 80, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[21]), 160, 80, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[37]), 120, 100, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[11]), 140, 100, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[47]), 160, 100, 20, 20);
            //绿色面
            g.FillRectangle(getColorformStatus(cube_status[29]), 180, 60, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[5]), 200, 60, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[31]), 220, 60, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[20]), 180, 80, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[22]), 220, 80, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[46]), 180, 100, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[13]), 200, 100, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[44]), 220, 100, 20, 20);
            //蓝色面
            g.FillRectangle(getColorformStatus(cube_status[35]), 60, 60, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[1]), 80, 60, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[25]), 100, 60, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[18]), 60, 80, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[16]), 100, 80, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[40]), 60, 100, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[9]), 80, 100, 20, 20);
            g.FillRectangle(getColorformStatus(cube_status[38]), 100, 100, 20, 20);

            //各种线
            g.DrawLine(new Pen(Color.Teal, 1), 60, 20, 120, 20);
            g.DrawLine(new Pen(Color.Teal, 1), 60, 40, 120, 40);
            g.DrawLine(new Pen(Color.Teal, 1), 60, 140, 120, 140);
            g.DrawLine(new Pen(Color.Teal, 1), 60, 160, 120, 160);

            g.DrawLine(new Pen(Color.Teal, 1), 20, 60, 20, 120);
            g.DrawLine(new Pen(Color.Teal, 1), 40, 60, 40, 120);
            g.DrawLine(new Pen(Color.Teal, 1), 140, 60, 140, 120);
            g.DrawLine(new Pen(Color.Teal, 1), 160, 60, 160, 120);
            g.DrawLine(new Pen(Color.Black, 1), 180, 60, 180, 120);
            g.DrawLine(new Pen(Color.Teal, 1), 220, 60, 220, 120);
            g.DrawLine(new Pen(Color.Teal, 1), 200, 60, 200, 120);


            g.DrawLine(new Pen(Color.Black, 1), 60, 0, 60, 180);
            g.DrawLine(new Pen(Color.Teal, 1), 80, 0, 80, 180);
            g.DrawLine(new Pen(Color.Teal, 1), 100, 0, 100, 180);
            g.DrawLine(new Pen(Color.Black, 1), 120, 0, 120, 180);
            g.DrawLine(new Pen(Color.Black, 1), 0, 60, 240, 60);
            g.DrawLine(new Pen(Color.Teal, 1), 0, 80, 240, 80);
            g.DrawLine(new Pen(Color.Teal, 1), 0, 100, 240, 100);
            g.DrawLine(new Pen(Color.Black, 1), 0, 120, 240, 120);



            if (All_Scan_OK && (currentStatus == 0))
            {
                System.Text.ASCIIEncoding ASCII = new System.Text.ASCIIEncoding();
                string Scan_Result = ASCII.GetString(cube_status);




                for (int x = 1; x < 20; x++)
                {
                    int temp = (x < 13 ? 3 * x - 1 : 4 * x - 13);
                    Scan_Result = Scan_Result.Insert(temp, " ");

                }
                

                All_Scan_OK = false;
                String Calc_Result = RubikSolve.GetResult(Scan_Result);
                textBox1.Text += DateTime.Now.ToString("hh:mm:ss") + " 步骤计算结果:" + Calc_Result + "\r\n"; //results
                textBox1.SelectionStart = textBox1.Text.Length;
                textBox1.ScrollToCaret();

                byte[] frameHead = { 0xfe, 0xAA };
                byte[]  Buffer = System.Text.Encoding.Default.GetBytes(Calc_Result);                     
                byte[] frameend = { 0x8A };
                if (serialPort1.IsOpen)                                     
                {
                    try
                    {
                        serialPort1.Write(frameHead, 0, 2);                   
                        Thread.Sleep(10);
                        serialPort1.Write(Buffer, 0, Buffer.Length);                    //写数据
                        Thread.Sleep(10);
                        serialPort1.Write(frameend, 0, 1);
                        Thread.Sleep(10);
                        //sw.Stop();
                        //timer2.Stop();
                    }
                    catch
                    {
                        MessageBox.Show("串口数据发送出错，请检查.", "错误");//错误处理
                    }
                }

            }
        }



        private void button2_Click_1(object sender, EventArgs e)
        {

            byte[] frameHead = { 0xfe, 0xAA };
            byte[] Buffer = { 70, 80, 90, 100, 80, 70, 90, 50, 50, 50, 50, 50, 5, 05, 05, 0, 4, 45, 12, 32, 65, 6, 2, 58, 6, 21, 31 };                   //定义数组
            byte[] frameend = { 0x8A };
            serialPort1.Write(frameHead, 0, 2);                    //写数据
            Thread.Sleep(10);
            serialPort1.Write(Buffer, 0, Buffer.Length);                    //写数据
            Thread.Sleep(10);
            serialPort1.Write(frameend, 0, 1);
            Thread.Sleep(10);
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            ts = sw.Elapsed;
            label2.Text = string.Format("{0}:{1}:{2}:{3}", ts.Hours, ts.Minutes, ts.Seconds, ts.Milliseconds);
        }




    }
}