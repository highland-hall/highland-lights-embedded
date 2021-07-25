# Highland Lights Protocol

## Header 
Each Protocol message is sent with a 1 byte version header. The current 8 bit version number is `0x00`. This is followed by a message type (a single byte) which are the following:
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
* `0x0A` Finalize light config
* `0x10` Set Range RGB
* `0x11` Set Range HSV
* `0x12` Set Strip RGB
* `0x13` Set Strip HSV


## Config messages
### Network configuration
After the header is transmited the following message format is used to transfer the network ssid and network:
```
|ssid_len(1)|ssid(ssid_len)|pass_len(1)|pass(pass_len)|
```

### Add Strip
Add a strip with a given index and number of leds

```
|strip_idx(1)|num_leds(2)|
```

### Test Strip
This is used to illuminate an entire strip to test.

```
|strip_idx(1)|
```

### Add Range
Add a strip with a given index and number of leds

```
|strip_idx(1)|start_idx(2)|end_idx(2)|
```

### Test Range
This is used to illuminate an entire strip to test.

```
|range_idx(4)|
```
### Finalize Light config
Finalizes the light config and stores it to eeprom on the controller. Ends config.

### Set Range RGB
Sets a given range to a given RGB Value

```
|range_idx(4)|R(1)|G(1)|B(1)|
```
### Set Range HSV
Sets a given range to a given RGB Value

```
|range_idx(4)|H(1)|S(1)|V(1)|
```
### Set Strip RGB
Sets a given range to a given RGB Value

```
|strip_idx(1)|R(1)|G(1)|B(1)|
```
### Set Strip HSV
Sets a given range to a given RGB Value

```
|strip_idx(4)|H(1)|S(1)|V(1)|
```
