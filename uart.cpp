/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: uart
 *** Description: uart for RPI /dev/ttyAMA0 Parity Check: None DB: 8 stop bit 1 
 *** Version: 
 ***     0.0: 2018-03-23/4DIAC-IDE - 4DIAC-Consortium - 
 ***     1.0: 2016-05-26/AZ - fortiss GmbH - 
 *************************************************************************/

#include "uart.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "uart_gen.cpp"
#endif
#include  <stdio.h>      /*标准输入输出定义*/

#include <stdlib.h>     /*标准函数库定义*/

#include <unistd.h>     /*Unix 标准函数定义*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
//#define BAUDRATE        B115200
#define UART_DEVICE     "/dev/ttyAMA0"

#define FALSE  -1
#define TRUE   0
DEFINE_FIRMWARE_FB(FORTE_uart, g_nStringIduart)

const CStringDictionary::TStringId FORTE_uart::scm_anDataInputNames[] = {g_nStringIdBaudRate, g_nStringIdDataBits, g_nStringIdStopbits, g_nStringIdParity, g_nStringIdsendMSG};

const CStringDictionary::TStringId FORTE_uart::scm_anDataInputTypeIds[] = {g_nStringIdDINT, g_nStringIdINT, g_nStringIdINT, g_nStringIdINT, g_nStringIdSTRING};

const CStringDictionary::TStringId FORTE_uart::scm_anDataOutputNames[] = {g_nStringIdConnectionState};

const CStringDictionary::TStringId FORTE_uart::scm_anDataOutputTypeIds[] = {g_nStringIdSTRING};

const TForteInt16 FORTE_uart::scm_anEIWithIndexes[] = {0, 5};
const TDataIOID FORTE_uart::scm_anEIWith[] = {0, 1, 2, 3, 255, 4, 255};
const CStringDictionary::TStringId FORTE_uart::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_uart::scm_anEOWith[] = {0, 255};
const TForteInt16 FORTE_uart::scm_anEOWithIndexes[] = {0, -1, -1};
const CStringDictionary::TStringId FORTE_uart::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const CStringDictionary::TStringId FORTE_uart::scm_anInternalsNames[] = {g_nStringIdfd};

const CStringDictionary::TStringId FORTE_uart::scm_anInternalsTypeIds[] = {g_nStringIdINT};

const SFBInterfaceSpec FORTE_uart::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  5,  scm_anDataInputNames, scm_anDataInputTypeIds,
  1,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


const SInternalVarsInformation FORTE_uart::scm_stInternalVars = {1, scm_anInternalsNames, scm_anInternalsTypeIds};
///////////////////////////////////////////////////////////////////
/**
*@brief  设置串口通信速率
*@param  fd     类型 int  打开串口的文件句柄
*@param  speed  类型 int  串口速度
*@return  void
*/

void set_speed(int fd, int speed){
	
int speed_arr[] = {B115200, B38400, B19200, B9600, B4800, B2400, B1200, B300,
                   B115200, B38400, B19200, B9600, B4800, B2400, B1200, B300, };
int name_arr[] = {115200, 38400, 19200, 9600, 4800, 2400, 1200,  300, 
                  115200, 38400, 19200, 9600, 4800, 2400, 1200,  300, };
  int   i; 
  int   status; 
  struct termios   Opt;
  tcgetattr(fd, &Opt); 
  for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++) { 
    if  (speed == name_arr[i]) {     
      tcflush(fd, TCIOFLUSH);     
      cfsetispeed(&Opt, speed_arr[i]);  
      cfsetospeed(&Opt, speed_arr[i]);   
      status = tcsetattr(fd, TCSANOW, &Opt);  
      if  (status != 0) {        
        perror("tcsetattr fd1");  
        return;     
      }    
      tcflush(fd,TCIOFLUSH);   
    }  
  }
}

///////////////////////////////////////////////////////////////////
/**
*@brief   设置串口数据位，停止位和效验位
*@param  fd     类型  int  打开的串口文件句柄
*@param  databits 类型  int 数据位   取值 为 7 或者8
*@param  stopbits 类型  int 停止位   取值为 1 或者2
*@param  parity  类型  int  效验类型 取值为N,E,O,,S
*/
int set_Parity(int fd,int databits,int stopbits,int parity)
{ 
    struct termios options; 
    if  ( tcgetattr( fd,&options)  !=  0) { 
        perror("SetupSerial 1");     
        return(FALSE);  
    }
    options.c_cflag &= ~CSIZE; 
    switch (databits) /*设置数据位数*/
    {   
    case 7:     
        options.c_cflag |= CS7; 
        break;
    case 8:     
        options.c_cflag |= CS8;
        break;   
    default:    
        fprintf(stderr,"Unsupported data size\n"); return (FALSE);  
    }
    switch (parity) 
    {   
	    case 1:
        case 'n':
        case 'N':    
            options.c_cflag &= ~PARENB;   /* Clear parity enable */
            options.c_iflag &= ~INPCK;     /* Enable parity checking */ 
            break;  
		case 2:	
        case 'o':   
        case 'O':     
            options.c_cflag |= (PARODD | PARENB); /* 设置为奇效验*/  
            options.c_iflag |= INPCK;             /* Disnable parity checking */ 
            break; 
        case 3:			
        case 'e':  
        case 'E':   
            options.c_cflag |= PARENB;     /* Enable parity */    
            options.c_cflag &= ~PARODD;   /* 转换为偶效验*/     
            options.c_iflag |= INPCK;       /* Disnable parity checking */
            break;
		case 4:
        case 'S': 
        case 's':  /*as no parity*/   
            options.c_cflag &= ~PARENB;
            options.c_cflag &= ~CSTOPB;break;  
        default:   
            fprintf(stderr,"Unsupported parity\n");    
            return (FALSE);  
        }  
    /* 设置停止位*/  
    switch (stopbits)
    {   
        case 1:    
            options.c_cflag &= ~CSTOPB;  
            break;  
        case 2:    
            options.c_cflag |= CSTOPB;  
           break;
        default:    
             fprintf(stderr,"Unsupported stop bits\n");  
             return (FALSE); 
    } 
    /* Set input parity option */ 
    if (parity != 'n')   
        options.c_iflag |= INPCK; 
    tcflush(fd,TCIFLUSH);
    options.c_cc[VTIME] = 150; /* 设置超时15 seconds*/   
    options.c_cc[VMIN] = 0; /* Update the options and do it NOW */
    if (tcsetattr(fd,TCSANOW,&options) != 0)   
    { 
        perror("SetupSerial 3");   
        return (FALSE);  
    } 
    options.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);  /*Input*/
    options.c_oflag  &= ~OPOST;   /*Output*/
    return (TRUE);  
}
///////////////////////////////////////////////////////////////////

void FORTE_uart::setInitialValues(){
  BaudRate() = 115200;
  DataBits() = 8;
  Stopbits() = 1;
  Parity() = 1;
}

void FORTE_uart::alg_initialize(void){
    fd() = open(UART_DEVICE, O_RDWR|O_RDONLY|O_NDELAY);
	if (fd() < 0) 
    {
        perror(UART_DEVICE);
        exit(1);
		ConnectionState() = "open device failed";
    }

    printf("Open...\n");
    set_speed(fd(),BaudRate());
    if (set_Parity(fd(),DataBits(),Stopbits(),Parity()) == FALSE)  
    {
        printf("Set Parity Error\n");
		ConnectionState() = "Set Parity Error!";
        exit (0);
    }
    ConnectionState() = "OK";
	printf("Open success!\n");
}

void FORTE_uart::alg_send(void){
            printf("Entering send fun!\n");  
			char *info = sendMSG().getValue();
	        int len = 0;
            int len_send = 0;
			len_send = strlen(info);
			if(len_send>=1)//有数据才发
			{
				len = write(fd(),info,len_send);    
				if(len > 0)    
				  { printf("Send %d data successful\n",len);  }  
				else    
				  { printf("Send data failed!\n");}  

				
					
			}
			else{
				printf("no data to send!\n");
			}
}


void FORTE_uart::enterStateSTART(void){
  m_nECCState = scm_nStateSTART;
}

void FORTE_uart::enterStateInit(void){
  m_nECCState = scm_nStateInit;
  alg_initialize();
  sendOutputEvent( scm_nEventINITOID);
}

void FORTE_uart::enterStateSend(void){
  m_nECCState = scm_nStateSend;
  alg_send();
  sendOutputEvent( scm_nEventCNFID);
}

void FORTE_uart::enterStateNarmal(void){
  m_nECCState = scm_nStateNarmal;
}

void FORTE_uart::executeEvent(int pa_nEIID){
  bool bTransitionCleared;
  do{
    bTransitionCleared = true;
    switch(m_nECCState){
      case scm_nStateSTART:
        if(scm_nEventINITID == pa_nEIID)
          enterStateInit();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateInit:
        if(1)
          enterStateNarmal();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateSend:
        if(1)
          enterStateNarmal();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scm_nStateNarmal:
        if(scm_nEventREQID == pa_nEIID)
          enterStateSend();
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      default:
      DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 3.", m_nECCState.operator TForteUInt16 ());
        m_nECCState = 0; //0 is always the initial state
        break;
    }
    pa_nEIID = cg_nInvalidEventID;  // we have to clear the event after the first check in order to ensure correct behavior
  }while(bTransitionCleared);
}


