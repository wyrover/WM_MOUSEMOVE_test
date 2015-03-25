WM_MOUSEMOVE_test
====
WM_MOUSEMOVEメッセージが送られてくる頻度は、マウス、タッチパネル、タッチパッドなどの入力デバイス毎に異なるのか？を調べるために作成したプログラム。

結果
----

|device                                             |message/sec|
|---------------------------------------------------|-----------|
|タッチパッド (Macbook Pro + BootCamp(Win8.1))      |     148.41|
|タッチパッド (Surface Pro 3 + Type Cover Keyboard) |     139.28|
|Microsoft Wheel Mouse Optical (USB)                |     128.04|
|Lenovo Mini Wireless Keyboard N5901 (USBワイヤレス)|     118.48|
|Surface Pro 3 タッチパネル                         |     101.63|
|Logicool M555b (Bluetooth)                         |      88.89|
|Lenovo ThinkPad Trackpoint Keyboard 0B47208 (USB)  |      65.27|

PCの構成によって結果は異なると考えられるが、参考まで。

