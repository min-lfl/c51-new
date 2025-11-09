#include <REGX52.H> //c52库
#include <I2C.H>

//配置AT24C02的地址是
#define AT24C02_ADDRESS 0xA0


/**
	* @brief		AT24C02写入函数，内置了等待写入完成
	* @param		要写入的地址，对AT24C02的8K型号来说最大地址0~255
	* @param		要写入的数据，最长为1字节
	* @retval		返回0表示写入成功，返回1表示写入超时
	*/
bit write_AT24C02(unsigned char ADDRESS,Byte){
	unsigned char ack;//定义一个变量来保存应答
	unsigned int timeout = 0;//定义一个变量来自加判断超时
	
	//写入的主体部分
	start_I2C();
	write_I2C(AT24C02_ADDRESS);
	r_I2c();  //接受一个应答，可以用来判断，不过我们这里不做判断
	write_I2C(ADDRESS);
	r_I2c();
	write_I2C(Byte);
	r_I2c();
	stop_I2C();
	
	
	//等待写入完成就跳出循环（因为写入会有5ms的延迟，这个延迟内从设备无法做出任何应答，包括读写，所以干脆写完后把这5ms等待完）
	do{
		start_I2C();
		write_I2C(AT24C02_ADDRESS);//呼喊一下从设备
		ack=r_I2c();//接收一下回应
		stop_I2C();
		if(timeout++ > 10000){return 1;}//返回1就是超时后还没有写入完成
	}while(ack!=0);//收到回应就是设备写入完成了，跳出循环
	
	return 0;//返回0就是写入完成
}


/**
	* @brief		AT24C02接收函数，在特定地址位接收一个数据
	* @param		要在哪个地址接收
	* @retval		接收到的数据
	*/
unsigned char  read_AT24C02(unsigned char ADDRESS){
	unsigned char date=1;
	start_I2C();
	write_I2C(AT24C02_ADDRESS);//选择哪个设备发送
	r_I2c();
	write_I2C(ADDRESS);//发送要读哪位
	r_I2c();
	
	//从这里开始读
	start_I2C();
	write_I2C(AT24C02_ADDRESS|0x01);//选择哪个设备接收
	r_I2c();
	date=read_I2C();//开始接收
	s_I2c(1);//接收完最后一个字节数据后主机要发送无应答
	stop_I2C();
	return date;
}



