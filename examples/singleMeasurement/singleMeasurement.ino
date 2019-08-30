/*!
 * @file singleMeasurement.ino
 * @brief 在单次读取模式下，读取环境温度(°C/F)和相对湿度(%RH)
 * @n 实验现象：芯片默认在此模式，我们需要发送指令去让芯片采集数据,需要设置读取的
 * @n 可重复性(芯片在两次相同测量条件下测量到的数据的差值), 然后读取温湿度数据,会在
 * @n 串口打印温度和湿度数据.
 * @n 单次采集模式:根据需要去读取数据，功耗较低，芯片的idle状态所需电流只需 0.5 微安
 * 
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2019-08-21
 * @get from https://www.dfrobot.com
 * @url https://github.com/DFRobot/DFRobot_SHT3x
*/

#include <DFRobot_SHT3x.h>

/*!
 * @brief 构造函数
 * @param pWire I2C总线指针对象，构造设备，可传参数也可不传参数，默认Wire。
 * @param address 芯片IIC地址,共有两个可选地址0x44、0x45(默认为0x44)。
 * @param RST 芯片复位引脚，默认为4.
 * @n IIC地址是由芯片上的引脚addr决定。
 * @n 当ADR与VDD连接,芯片IIC地址为：0x45。
 * @n 当ADR与VSS连接,芯片IIC地址为：0x44。
 */
//DFRobot_SHT3x sht3x(&Wire,/*address=*/0x44,/*RST=*/4);

DFRobot_SHT3x   sht3x;

void setup() {
  Serial.begin(9600);
  //初始化芯片
  while (sht3x.begin() != 0) {
    Serial.println("初始化芯片失败，请确认芯片连线是否正确");
    delay(1000);
  }
  /**
   * readSerialNumber:读取芯片的序列号
   * @return 返回32位序列号
   */
  Serial.print("芯片序列号：");
  Serial.println(sht3x.readSerialNumber());
  
  /**
   * softReset：通过IIC发送命令复位，进入芯片的默认模式单次测量模式，关闭加热器，并清除ALERT引脚的警报。
   * @return 通过读取状态寄存器来判断命令是否成功被执行，返回true则表示成功
   */
   if(!sht3x.softReset()){
     Serial.println("芯片复位失败....");
   }
   
  /**
   * heaterEnable()： 打开芯片里面的加热器.作用是使传感器在潮湿的环境也能有准确的湿度数据
   * @return 通过读取状态寄存器来判断命令是否成功被执行，返回true则表示成功
   * @note 加热器的使用条件，应是在潮湿环境时，若正常情况下使用则会造成读数不准.
   */
  //if(!sht3x.heaterEnable()){
    // Serial.println("加热器打开失败....");
  //}
  Serial.println("------------------单次测量模式下读取数据-----------------------");
}

void loop() {
  /**
   * readTemperatureAndHumidity：单次测量模式下读取温湿度数据；需要使用getTemperatureC(),getTemperatureF(),getHumidityRH(),
                                 来接收数据
   * @param repeatability：
                    eRepeatability_High /**高可重复性模式下，湿度的可重复性为0.10%RH，温度的可重复性为0.06°C
                    eRepeatability_Medium,/**中等可重复性模式下，湿度的可重复性为0.15%RH，温度的可重复性为0.12°C
                    eRepeatability_Low, /**低可重复性模式下，湿度的可重复性为0.25%RH，温度的可重复性为0.24°C
   * @return 返回true表示数据获取成功
   */
  if(sht3x.readTemperatureAndHumidity(sht3x.eRepeatability_High)){
    Serial.print("环境温度(°C/F):");
    /**
     * getTemperatureC:获取测量到的温度(单位：摄氏度)
     * @return 返回float类型的温度数据
     */
    Serial.print(sht3x.getTemperatureC());
    Serial.print(" C/");
    /**
     * getTemperatureF:获取测量到的温度(单位：华氏度)
     * @return 返回float类型的温度数据
     */
    Serial.print(sht3x.getTemperatureF());
    Serial.print(" F      ");
    Serial.print("相对湿度(%RH):");
    /**
     * getHumidityRH :获取测量到的湿度(单位：%RH)
     * @return 返回float类型的湿度数据
     */
    Serial.print(sht3x.getHumidityRH());
    Serial.println(" %RH");
  }
  delay(5000);
}