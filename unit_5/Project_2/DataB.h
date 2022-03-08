/*
 * DataB.h
 *
 *  Created on: Mar 4, 2022
 *      Author: Hassan
 */

#ifndef DATAB_H_
#define DATAB_H_

#include "fifo.h"

/* API functions */
void add_student_manually(FIFO_buf_t* fifo);
void add_student_file(FIFO_buf_t* fifo);
element_type* check_roll(FIFO_buf_t* fifo,int Selected_Roll);
void find_rl(FIFO_buf_t* fifo);
void find_fn(FIFO_buf_t* fifo);
void find_c(FIFO_buf_t* fifo);
void tot_s(FIFO_buf_t* fifo);
void show_s(FIFO_buf_t* fifo);
void del_s(FIFO_buf_t* fifo,element_type* buffer);
void up_s(FIFO_buf_t* fifo);
#endif /* DATAB_H_ */
