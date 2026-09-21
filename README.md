# SafePass

Two-door static pass box controller based on ESP32-S3.

## Hardware

* Waveshare ESP32-S3-ETH-8DI-8RO / ESP32-S3-POE-8DI-8RO
* TCA9554 I/O expander
* 2 × electromagnetic locks
* 2 × magnetic lock-status sensors
* 2 × pushbuttons
* Red and green indicators for each door

## Input Mapping

| Channel |   GPIO | Function     |
| ------- | -----: | ------------ |
| DI1     |  GPIO4 | Pushbutton A |
| DI2     |  GPIO5 | LockStatus A |
| DI3     |  GPIO6 | Unused       |
| DI4     |  GPIO7 | Unused       |
| DI5     |  GPIO8 | Pushbutton B |
| DI6     |  GPIO9 | LockStatus B |
| DI7     | GPIO10 | Unused       |
| DI8     | GPIO11 | Unused       |

Inputs use `INPUT_PULLUP`.

```text
LOW  = Active
HIGH = Inactive
```

## Output Mapping

Outputs are controlled through TCA9554.

| Channel | Function |
| ------- | -------- |
| DO1     | Lock A   |
| DO2     | Green A  |
| DO3     | Red A    |
| DO4     | Unused   |
| DO5     | Lock B   |
| DO6     | Green B  |
| DO7     | Red B    |
| DO8     | Unused   |

TCA9554 address:

```text
0x20
```

I2C:

```text
SDA = GPIO42
SCL = GPIO41
```

The electromagnetic locks must be driven through a suitable driver/relay interface. Do not connect the locks directly to the TCA9554.

## LockStatus

The magnetic sensor is mounted on the door leaf.

```text
Sensor sticks to lock
        ↓
Physically locked

Sensor separates from lock
        ↓
Physically unlocked
```

The firmware separates:

```text
Lock::isLocked()
        = commanded state

LockStatus::isLocked()
        = physical feedback
```

## Interlock

States:

```text
IDLE
RELEASE_A
DOOR_A_OPEN
WAIT_LOCK_A
RELEASE_B
DOOR_B_OPEN
WAIT_LOCK_B
FAULT
```

Normal sequence:

```text
IDLE
 ↓
Release Door A
 ↓
Door A physically unlocked
 ↓
Door A opened
 ↓
Door A physically locked
 ↓
WAIT_LOCK_A
 ↓
Lock command + physical confirmation
 ↓
IDLE
```

Door B follows the same sequence.

Only one door can be released at a time.

## Timeouts

```text
Unlock timeout          = 5 seconds
Lock confirmation       = 1 second
Fault reset hold        = 3 seconds
Fault indicator blink   = 500 ms
Input debounce          = 100 ms
```

All timing is non-blocking using `millis()`.

## Fault

The controller enters `FAULT` for unsafe conditions such as:

* Both doors physically unlocked
* Both lock commands unlocked
* Lock command failure
* Lock confirmation timeout
* Unexpected physically unlocked door while in `IDLE`

During `FAULT`:

```text
Green A = OFF
Green B = OFF

Red solid    = physically unsafe
Red blinking = physically safe
```

Fault reset requires both pushbuttons to be held for 3 seconds, with both doors physically locked.

## Version

```text
v0.1.0
```

Current version is the stable two-door interlock baseline.

UV sterilization and timer functionality are not included in this version.
