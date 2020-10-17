#ifndef AIC_FUNC_H_
#define AIC_FUNC_H_

void AIC_init(void);
void AIC_off(void);
void AIC_read2(Int16*, Int16*);
void AIC_write2(Int16, Int16);
void AIC_wait_read();
void AIC_wait_write();

#endif /*AIC_FUNC_H_*/
