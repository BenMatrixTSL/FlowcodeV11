# Flowcode Component Quick Reference Guide

## API Type Reference

| Type | Description | Usage | Example |
|------|-------------|-------|---------|
| `0` | Private API | Internal helper functions | `Prv_CalculateChecksum` |
| `1` | Public API | User-visible functions | `Send`, `Receive` |
| `2` | Property Accessor | GetValue/SetValue/GetList | `GetValue`, `SetValue` |
| `5` | Code Generation | Generates C code for embedded | `FC_Component_$(macro)_$(instance)` |

## Variable Type Reference

| Type | Description | Size | Example Usage |
|------|-------------|------|---------------|
| `u8` | Unsigned 8-bit integer | 1 byte | Pin numbers, counters |
| `u16` | Unsigned 16-bit integer | 2 bytes | ADC readings, timers |
| `u32` | Unsigned 32-bit integer | 4 bytes | Timestamps, large counters |
| `s8` | Signed 8-bit integer | 1 byte | Small signed values |
| `s16` | Signed 16-bit integer | 2 bytes | Sensor readings |
| `s32` | Signed 32-bit integer | 4 bytes | Large signed values |
| `b1` | Boolean | 1 bit | Flags, true/false |
| `T8` | String/Character array | Variable | Text data, buffers |
| `T8*` | String pointer | 4 bytes | String parameters |
| `f32` | 32-bit float | 4 bytes | Temperature, measurements |
| `h32` | Handle | 4 bytes | Object handles |
| `v0` | Void | 0 bytes | No return value |

## Property Type Reference

| TypeID | Description | Example |
|--------|-------------|---------|
| `5` | Pin selection | `$PORTA.0` |
| `7` | Boolean (Yes/No) | `0` or `1` |
| `10` | String | `"Hello"` |
| `14` | Integer | `9600` |
| `16` | Dropdown list | `000Option1\n001Option2` |
| `21` | Unsigned integer | `100` |

## Common Event Handlers

| Event | Class | Purpose |
|-------|-------|---------|
| `Ev_Initialise` | Components | Component initialization |
| `Ev_Property_Change` | Components | Property value changed |
| `Ev_ChipChange` | Connection | Target device changed |
| `Ev_AddHeader` | Compile | Add header code |
| `Ev_AddProperty` | Compile | Modify properties at compile time |
| `Ev_Start` | Simulation | Simulation started |
| `Ev_Stop` | Simulation | Simulation stopped |
| `Ev_Timer` | System | Timer callback |

## Command Types in Macros

| Command Type | Purpose | Example |
|--------------|---------|---------|
| `calculation` | Assign values, math | `result = value1 + value2` |
| `call` | Call another macro | `macro='HelperFunction'` |
| `decision` | If/else branching | `exp='value > 100'` |
| `loop` | Iteration | `exp='i < 10'` |
| `sim` | Simulation-only code | `macro='Component.Property.GetValue'` |
| `switch` | Multi-way branching | `exp='value'` with cases |

## Multiple Instances - Important Difference

### Arduino vs Flowcode Instance Handling

| Aspect | Arduino | Flowcode |
|--------|---------|----------|
| **Instance Management** | Uses object instances/pointers | Automatic via instance numbers |
| **Variable Access** | `this->variable` or `instance->variable` | Direct access: `variable` |
| **Function Names** | Same name, different objects | Auto-renamed: `Function_1()`, `Function_2()` |
| **Variable Names** | Same name, different objects | Auto-renamed: `variable_1`, `variable_2` |
| **Code Required** | Must create object instances | No special code needed |

**Key Point:** When converting Arduino libraries, **remove all pointer/object instance handling**. Flowcode automatically appends instance numbers to all variables and functions.

**Example:**
```cpp
// Arduino - requires object instance
MySensor sensor1(5);
sensor1.begin();
int val = sensor1.read();
```

```xml
<!-- Flowcode - no instance handling needed -->
<!-- Variables automatically become sensorPin_1, sensorPin_2, etc. -->
<!-- Functions automatically become FC_MySensor_Read_1(), FC_MySensor_Read_2(), etc. -->
```

## Arduino to Flowcode Mapping

### Function Mapping

| Arduino | Flowcode API | Notes |
|---------|--------------|-------|
| `begin()` | `Initialise` | Standard initialization |
| `read()` | `Read` | Read sensor/data |
| `write()` | `Write` | Write data |
| `available()` | `Available` | Check if data ready |
| `setMode()` | `SetMode` | Configuration |
| `getValue()` | `GetValue` | Retrieve value |

### Instance Handling Mapping

| Arduino Pattern | Flowcode Pattern | Notes |
|----------------|------------------|-------|
| `class MyLib { ... }` | Remove class, use `<variables>` | No class structure needed |
| `MyLib instance(pin);` | No object creation | Flowcode handles instances |
| `instance.begin();` | Call `Initialise` API | Direct function call |
| `this->variable` | `variable` | Direct variable access |
| `instance->variable` | `variable` | Direct variable access |
| Constructor | `Ev_Initialise` event | Use initialization event |

### Variable Mapping

| Arduino Type | Flowcode Type | Notes |
|--------------|---------------|-------|
| `int` | `s16` or `s32` | Depends on size needed |
| `unsigned int` | `u16` or `u32` | Depends on size needed |
| `byte` | `u8` | 8-bit value |
| `bool` | `b1` | Boolean |
| `float` | `f32` | 32-bit float |
| `char*` | `T8*` | String pointer |
| `char[]` | `T8` with array | Character array |

### Common Patterns

**Pattern: Initialization**
```cpp
// Arduino
void begin(int pin);
```
```xml
<!-- Flowcode -->
<api name='Initialise' alt='FC_Component_$(macro)_$(instance)' type='5' />
<param name='Pin' type='u8' />
```

**Pattern: Read Function**
```cpp
// Arduino
int read();
```
```xml
<!-- Flowcode -->
<api name='Read' alt='FC_Component_$(macro)_$(instance)' type='5' />
<return name='Return' type='s16' />
```

**Pattern: Configuration**
```cpp
// Arduino
void setBaudRate(int baud);
```
```xml
<!-- Option 1: API -->
<api name='SetBaudRate' alt='FC_Component_$(macro)_$(instance)' type='5' />

<!-- Option 2: Property (if set once) -->
<property name='Baud Rate' target='BAUD' typeid='14' />
```

## Template Variables

Use these in `alt` attributes for API names:

- `$(macro)` - The macro/function name
- `$(instance)` - Component instance number
- `$(variable)` - Property variable name

**Example:**
```xml
<api name='Send' alt='FC_UART_$(macro)_$(instance)' type='5' />
```
Generates: `FC_UART_Send_1`, `FC_UART_Send_2`, etc.

## Common Property Filters

**Baud Rates:**
```
000Custom
0011200
0022400
0034800
0049600
00519200
00638400
00757600
008115200
```

**Data Bits:**
```
0077 Bits
0088 Bits
0099 Bits
```

**Boolean:**
```
000No
001Yes
```

**On/Off:**
```
000Off
001On
```

## File Structure Checklist

When creating a new component, ensure you have:

- [ ] `<definition>` with GUID, name, description
- [ ] `<properties>` for user configuration
- [ ] `<values>` with default property values
- [ ] `<events>` for system callbacks
- [ ] `<apis>` for public/private functions
- [ ] `<variables>` for global state
- [ ] `<macros>` implementing each API
- [ ] Event handler macros (e.g., `Ev_Initialise`)

## Naming Conventions

- **APIs**: PascalCase (e.g., `ReadTemperature`, `SendData`)
- **Private APIs**: Prefix with `Prv_` (e.g., `Prv_CalculateCRC`)
- **Variables**: camelCase or snake_case (e.g., `sensorPin` or `sensor_pin`)
- **Properties**: Descriptive names (e.g., `Sensor Pin`, `Baud Rate`)
- **Macros**: Match API names exactly

## Common Mistakes to Avoid

1. **Missing Event Handlers**: If you declare an event, you must implement the macro
2. **Type Mismatches**: Ensure variable types match their usage
3. **Missing Return Values**: APIs that return values must have `<return>` in macro
4. **Incorrect API Types**: Use type 5 for code generation, type 1 for simulation-only
5. **Property Without Default**: Always provide default values in `<values>` section
6. **Using Pointers/Objects**: Flowcode handles instances automatically - remove all `this->`, `->`, and object instance code
7. **Missing Instance Numbers**: Always include `$(instance)` in API `alt` attributes for type 5 APIs
8. **Trying to Manage Instances Manually**: Don't create instance management code - Flowcode does this automatically

## Embedded Components

### Common Embedded Component Types

| Component Type | Codename | Purpose | Example Usage |
|----------------|----------|---------|---------------|
| I2C CAL | `cal_i2c1` | I2C communication | `component='cal_i2c1' macro='Transaction_Read'` |
| SPI CAL | `cal_spi1` | SPI communication | `component='cal_spi1' macro='Transaction'` |
| UART CAL | `cal_uart1` | UART communication | `component='cal_uart1' macro='Send'` |
| Lookup Table | `RawDataLUT` | Data conversion | `RawDataLUT::GetInt(.idx)` |
| Math | Various | Mathematical operations | Various math functions |

### Referencing Embedded Component Properties

```xml
<!-- Property reference -->
<property name='Channel' target='cal_i2c1::CHANNEL' typeid='16' />

<!-- Value reference -->
<value target='cal_i2c1::CHANNEL' data='001' />
```

### Calling Embedded Component Macros

```xml
<!-- Call macro from embedded component -->
<command class_type='call' component='cal_i2c1' macro='Master_Init' />
<command class_type='call' component='cal_i2c1' macro='Transaction_Read'>
  <argument exp='.Buff' />
  <argument exp='5' />
</command>
```

### Lookup Table Usage

```xml
<!-- Access LUT values -->
<command class_type='calculation' title='Calculation'>
  <exp exp='value = RawDataLUT::GetInt(.idx)' />
  <exp exp='float_value = MpsDataLUT::GetFloat(.idx)' />
</command>
```

## Error Handling Patterns

### CRC/Checksum Validation
```xml
<!-- Calculate checksum -->
<command class_type='loop' title='Loop' type='0' exp='.idx < length'>
  <flowline>
    <command class_type='calculation' title='Calculation'>
      <exp exp='.sum = .sum + .Buff[.idx]' />
    </command>
  </flowline>
</command>

<!-- Validate -->
<command class_type='decision' title='CRC OK?' exp='.check = 0' swap='0'>
  <flowline>
    <!-- Valid - process data -->
  </flowline>
  <flowline>
    <!-- Invalid - return error or last value -->
  </flowline>
</command>
```

### Range Checking
```xml
<command class_type='decision' title='Decision' exp='value < MIN_VALUE' swap='0'>
  <flowline>
    <command class_type='calculation' title='Calculation'>
      <exp exp='.Return = 0' />
    </command>
  </flowline>
  <flowline>
    <command class_type='decision' title='Decision' exp='value > MAX_VALUE' swap='0'>
      <flowline>
        <command class_type='calculation' title='Calculation'>
          <exp exp='.Return = MAX_VALUE' />
        </command>
      </flowline>
      <flowline>
        <!-- In range - process normally -->
      </flowline>
    </command>
  </flowline>
</command>
```

## Testing Checklist

- [ ] Component loads without errors
- [ ] Properties are visible and editable
- [ ] APIs appear in function list
- [ ] Public variables are accessible
- [ ] Code compiles for target device
- [ ] Simulation works correctly
- [ ] Event handlers fire appropriately
- [ ] Embedded components initialize correctly
- [ ] Error handling works (CRC, range checks)
- [ ] Lookup tables return correct values

