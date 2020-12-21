# Highland Lights Protocol

## Header 
Each Protocol message is sent with a 2 byte version header. The current 16 bit version number is `0x0000`. This is followed by a message type (a single byte) which are the following:
* `0x00` Nack
* `0x01` Ack
* `0x02` network config (containing wifi ssid and pass)
* `0x03` Test strip
* `0x04` Add strip
* `0x05` Remove strip
* `0x06` Test range
* `0x07` Add range
* `0x08` Remove range
* `0x09` Get light config

## Config messages
### Network configuration
After the header is transmited the following message format is used to transfer the network ssid and network:
```
|ssid_len(1)|ssid(ssid_len)|pass_len(1)|pass(pass_len)|
```

