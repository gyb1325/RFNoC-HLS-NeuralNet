#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "test_conv.h"


int main_test1()
{
  data_t test1_data[TEST1_N_IN][2] =
          { 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9 };

  float test1_ref[TEST1_N_OUT][TEST1_CHAN_OUT] = 
          {12.5, 20.5, 28.5, 36.5, 44.5, 52.5, 60.5};

  hls::stream<data_t> data_i, data_q;
  for (int ii = 0; ii < TEST1_N_IN; ii++){
    data_i << test1_data[ii][0];
    data_q << test1_data[ii][1];
  }

  // Run the basic neural net block
  hls::stream<result_t> res;
  test_conv(data_i, data_q, res);

  result_t resval;
  float err;
  int errcount = 0;
  for (int ii = 0; ii < TEST1_N_OUT; ii++) {
    resval = float(res.read());
    err = resval - test1_ref[ii][0];
    std::cout << "Received: " << resval << ", Err: " << err << std::endl;
    if (abs(err)>0.0001)  errcount++;
  }

  return  errcount;
}

int main_test2()
{
  data_t test2_data[TEST2_N_IN][2] =
          { 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9 };

  float test2_ref[TEST2_N_OUT][TEST2_CHAN_OUT] = 
          { 6*2+0.25,  6*4+0.50,  6*6+0.75, 
           10*2+0.25, 10*4+0.50, 10*6+0.75,
           14*2+0.25, 14*4+0.50, 14*6+0.75,
           18*2+0.25, 18*4+0.50, 18*6+0.75,
           22*2+0.25, 22*4+0.50, 22*6+0.75,
           26*2+0.25, 26*4+0.50, 26*6+0.75, 
           30*2+0.25, 30*4+0.50, 30*6+0.75};

  hls::stream<data_t> data_i, data_q;
  for (int ii = 0; ii < TEST2_N_IN; ii++){
    data_i << test2_data[ii][0];
    data_q << test2_data[ii][1];
  }

  // Run the basic neural net block
  hls::stream<result_t> res;
  test_conv(data_i, data_q, res);

  float err, resval, refval;
  int errcount = 0;
  for (int ii = 0; ii < TEST2_N_OUT; ii++) {
    for (int jj = 0; jj < TEST2_CHAN_OUT; jj++) {
      resval = float(res.read());
      refval = test2_ref[ii][jj];
      err = resval - refval;
      std::cout << "Row: " << ii << ", Chan: " << jj << ": " << resval << ", Ref: " << refval << ", Err: " << err << std::endl;
      if (abs(err)>0.0001)  errcount++;
    }
  }

  return  errcount;
}

int main(int argc, char **argv)
{
    // RUN TEST1
    // return main_test1();

    // RUN TEST2
    return main_test2();
}
