int main(void){

  int test[2] = {0,0};
  
  DD_SSHand_t g_ss_h[0] = {
    { .add = 0x16,    /*I2C address*/
      .data_size = 2, /*データサイズ*/
      .data = {0,0,0,0,0,0,0,0},/*受信データ格納関数の初期化*/
    }
  };

  while(1){
     if(__RC_ISPRESSED_CIRCLE(g_rc_data)){
	test[0] = g_ss_h[0].data[0];
	test[1] = g_ss_h[0].data[1];
     }
  }
  
}
