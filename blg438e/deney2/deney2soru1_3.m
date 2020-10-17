num = [1 1 1 1]; %%pay
denum=[4]; %%payda

transfer_func = filt(num, denum)
bode(transfer_func)