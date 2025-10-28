PUSH 10
CALL :time_need_to_do_task
CALL :time_need_to_do_task
CALL :time_need_to_do_task
CALL :time_need_to_do_task
CALL :time_need_to_do_task
OUT
HLT

:time_need_to_do_task
PUSH 10
MUL
RET
