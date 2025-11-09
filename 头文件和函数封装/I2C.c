#include <REGX52.H> //c52库

sbit I2C_SCL=P2^1;
sbit I2C_SDA=P2^0;

/**
	* @brief		数据帧头，先SDA拉低，再SCL拉低
	* @param		无
	* @retval		无
	*/
void start_I2C(){
	I2C_SDA=1;
	I2C_SCL=1;
	I2C_SDA=0;
	I2C_SCL=0;
}

/**
	* @brief		数据帧尾，先SCL拉高，再SDA拉高
	* @param		无
	* @retval		无
	*/
void stop_I2C(){
	I2C_SCL=0;
	I2C_SDA=0;
	I2C_SCL=1;
	I2C_SDA=1;
}


/**
	* @brief		发送一个字节，由高位遍历到低位，SDA放入比特后，SCL输出脉冲发送比特，重复8次
	* @param		要发送的字节
	* @retval		无
	*/
void write_I2C(unsigned char Byte){
	unsigned char i;
	I2C_SCL=0;
	for(i=0;i<8;i++){
		I2C_SDA=Byte&(0x80>>i);
		I2C_SCL=1;
		I2C_SCL=0;
	}
}

/**
	* @brief		接收一个字节，把SDA拉高是把控制权交给从机，然后SCL发送一个脉冲就读取SDA一次，重复8次
	* @param		无
	* @retval		接收的字节
	*/
unsigned char read_I2C(){
	unsigned char i,date=0;
	I2C_SCL=0;
	I2C_SDA=1;  //把sda位 置为1，控制权交还给从机
	for(i=0;i<8;i++){
		I2C_SCL=1;
		if(I2C_SDA){date|=0x80>>i;}
		I2C_SCL=0;
	}
	return date;
}

/**
	* @brief		发送一个应答
	* @param		要发送的应答，参数0为应答，参数1为不应答
	* @retval		无
	*/
void s_I2c(char Bit){
	I2C_SDA=Bit;
	I2C_SCL=1;
	I2C_SCL=0;
}

/**
	* @brief		接受一个应答
	* @param		无
	* @retval		接受到的应答
	*/
char r_I2c(){
	char Bit=0;
	I2C_SDA=1;//把sda位 置为1，控制权交还给从机
	
	I2C_SCL=1;
	Bit=I2C_SDA;
	I2C_SCL=0;
	return Bit;
}