@echo off
echo ---------------------------------------
echo HM_UnionPi_CAT工程源码开始部署。。。
echo ---------------------------------------
set /p oh_path=请输入您的鸿蒙3.0源码路径(例如D:\OpenHarmony)：
xcopy %cd%\code\*.* %oh_path%\applications\sample\wifi-iot\app /e
if %errorlevel%==0 (echo 各模块demo源码部署成功！) else (echo 各模块demo源码部署失败！)
copy %cd%\BUILD.gn %oh_path%\applications\sample\wifi-iot\app && (echo BUILD.gn部署成功！) || (echo BUILD.gn部署失败！)
copy %cd%\usr_config.mk %oh_path%\device\hisilicon\hispark_pegasus\sdk_liteos\build\config && (echo usr_config.mk部署成功！) || (echo usr_config.mk部署失败！)
echo HM_UnionPi_CAT工程源码部署完毕！
pause