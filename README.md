# csmsd
SMS-sending tool.

Build: 
```
$ g++ csmsd.cpp -o csmsd
```

To use, run csmsd with parameters: csmsd port_where_modem_is_inserted +yours_phone 0 or 1 text message ;)

Example:
```
$ csmsd /dev/ttyUSB0 +79991234455 0 text message
```

