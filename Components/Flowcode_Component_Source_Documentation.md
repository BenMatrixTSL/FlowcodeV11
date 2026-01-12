# Flowcode Component Source File Documentation

## Overview

Flowcode component source files (`.fcfx`) are XML-based files that define reusable code libraries for embedded microcontrollers and PC/Web development. These components encapsulate functionality into visual blocks that can be dragged and dropped into Flowcode projects.

This document explains the structure of Flowcode component source files and provides guidance for converting Arduino libraries into Flowcode components.

---

## File Structure

A Flowcode component file is an XML document with the following main sections:

```xml
<root>
  <document>
    <components>
      <component class_type='root'>
        <properties>    <!-- Component configuration options -->
        <values>        <!-- Default property values -->
        <events>        <!-- System event handlers -->
        <apis>          <!-- Public/Private function definitions -->
        <variables>      <!-- Global variables -->
        <macros>        <!-- Functional code implementation -->
      </component>
    </components>
  </document>
</root>
```

---

## 1. APIs Section

The `<apis>` section defines the public interface of your component - the functions that users can call from their Flowcode programs.

### API Structure

```xml
<apis>
  <api name='FunctionName' alt='AlternativeName' type='Type' proto='1' />
</apis>
```

### API Attributes

- **`name`**: The function name as it appears to users (e.g., `Send`, `Receive`, `Initialise`)
- **`alt`**: Alternative name for code generation. Can use template variables:
  - `$(macro)` - The macro name
  - `$(instance)` - Component instance number
  - Example: `alt='FC_CAL_UART_$(macro)_$(instance)'` generates `FC_CAL_UART_Send_1`
- **`type`**: API visibility type:
  - `0` = Private (internal use only)
  - `1` = Public (visible to users)
  - `2` = Property accessor (GetValue/SetValue)
  - `5` = Code generation macro (generates C code)
- **`proto`**: Protocol version (usually `1`)
- **`enumfilter`**: Optional filter for enum values (e.g., `enumfilter='Sample_*'`)

### API Types Explained

#### Type 0: Private APIs
- Internal helper functions
- Not visible in the component's API list
- Used for code organization

#### Type 1: Public APIs
- User-visible functions
- Appear in the component's function list
- Can be called from user programs

#### Type 2: Property Accessors
- Special functions for property management
- `GetValue` - Retrieve property values
- `SetValue` - Set property values
- `GetList` - Get property option lists

#### Type 5: Code Generation Macros
- Generate actual C code for embedded targets
- Use `alt` attribute to define the generated function name
- Example: `alt='FC_CAL_UART_$(macro)_$(instance)'` creates `FC_CAL_UART_Send_1()`

### Example API Definitions

```xml
<!-- Public function visible to users -->
<api name='Send' alt='FC_CAL_UART_$(macro)_$(instance)' type='5' proto='1' />

<!-- Public function with simulation support -->
<api name='Receive' alt='FC_CAL_UART_$(macro)_$(instance)' type='5' proto='1' />

<!-- Property accessor -->
<api name='GetValue' alt='' type='2' proto='1' />

<!-- Private helper function -->
<api name='Prv_LoadFcdProperties' alt='Prv_LoadFcdProperties' type='0' proto='1' />
```

### Converting Arduino Functions to APIs

**Arduino Library Example:**
```cpp
class MySensor {
public:
    void begin();
    int read();
    void setMode(int mode);
};
```

**Flowcode API Equivalent:**
```xml
<apis>
  <api name='Initialise' alt='FC_MySensor_$(macro)_$(instance)' type='5' proto='1' />
  <api name='Read' alt='FC_MySensor_$(macro)_$(instance)' type='5' proto='1' />
  <api name='SetMode' alt='FC_MySensor_$(macro)_$(instance)' type='5' proto='1' />
</apis>
```

---

## 2. Variables Section

The `<variables>` section defines global variables used by the component. These can be public (accessible to users) or private (internal use only).

### Variable Structure

```xml
<variables>
  <variable public='0'>
    <def class_type='variable' 
         name='VariableName' 
         type='DataType' 
         description='Description text'
         isconst='0' 
         isHidden='0' 
         isinit='0' 
         usrinit='DefaultValue' 
         setinit='' />
    <array size='ArraySize' />  <!-- Optional: for arrays -->
  </variable>
</variables>
```

### Variable Attributes

- **`public`**: 
  - `0` = Private (internal use only)
  - `1` = Public (visible to users, can be accessed from user code)
- **`name`**: Variable name (must be valid C identifier)
- **`type`**: Data type. Common types:
  - `u8`, `u16`, `u32` - Unsigned integers (8, 16, 32 bit)
  - `s8`, `s16`, `s32` - Signed integers
  - `b1` - Boolean (1 bit)
  - `T8` - String/character array
  - `T8*` - String pointer
  - `f32` - 32-bit float
  - `h32` - Handle (32-bit handle type)
  - `v0` - Void (no return value)
- **`description`**: User-visible description
- **`isconst`**: `0` = variable, `1` = constant
- **`isHidden`**: `0` = visible, `1` = hidden from users
- **`isinit`**: `0` = not initialized, `1` = initialized
- **`usrinit`**: User-defined initial value
- **`setinit`**: System-set initial value

### Example Variable Definitions

```xml
<variables>
  <!-- Private variable for internal state -->
  <variable public='0'>
    <def class_type='variable' 
         name='tx_buffer' 
         type='u8' 
         description='Transmit buffer'
         isconst='0' 
         isHidden='0' 
         isinit='0' 
         usrinit='0' 
         setinit='' />
  </variable>

  <!-- Public constant visible to users -->
  <variable public='1'>
    <def class_type='variable' 
         name='Sample_Full' 
         type='s16' 
         description='Full width sample size'
         isconst='1' 
         isHidden='0' 
         isinit='1' 
         usrinit='1' 
         setinit='1' />
  </variable>

  <!-- String array variable -->
  <variable public='0'>
    <def class_type='variable' 
         name='temp_str' 
         type='T8' 
         description='Temporary string'
         isconst='0' 
         isHidden='0' 
         isinit='0' 
         usrinit='""' 
         setinit='' />
    <array size='100' />
  </variable>
</variables>
```

### Multiple Instances and Instance Management

**Important:** Flowcode handles multiple instances differently from Arduino libraries.

#### Arduino Approach (Object-Oriented)

Arduino libraries typically use object-oriented programming with pointers to avoid global variable conflicts:

```cpp
class MySensor {
private:
    int sensorPin;
    bool initialized;
    float lastReading;
    
public:
    MySensor(int pin) {
        sensorPin = pin;
        initialized = false;
    }
    
    void begin() {
        pinMode(sensorPin, INPUT);
        initialized = true;
    }
    
    int read() {
        return analogRead(sensorPin);
    }
};

// Usage - each instance has its own data
MySensor sensor1(5);   // Instance 1
MySensor sensor2(6);   // Instance 2
sensor1.begin();
sensor2.begin();
int value1 = sensor1.read();  // Reads from pin 5
int value2 = sensor2.read();  // Reads from pin 6
```

#### Flowcode Approach (Automatic Instance Isolation)

Flowcode automatically handles multiple instances by appending unique identifiers to all global variables and function names. **You do NOT need to use pointers or object instances.**

When a user adds multiple instances of your component to their project:
- Each instance gets a unique instance number (1, 2, 3, etc.)
- All global variables are automatically renamed with the instance number
- All API functions are automatically renamed with the instance number

**Example:**

If a user adds two instances of your component:

**Instance 1:**
- Variable `sensorPin` becomes `sensorPin_1`
- Function `Read()` becomes `FC_MySensor_Read_1()`

**Instance 2:**
- Variable `sensorPin` becomes `sensorPin_2`
- Function `Read()` becomes `FC_MySensor_Read_2()`

#### Converting Arduino Libraries: Removing Pointer/Instance Logic

When converting an Arduino library, **remove all pointer/object instance handling**. Simply define variables as global variables in the `<variables>` section.

**Arduino Library (with instance handling):**
```cpp
class MySensor {
private:
    int _pin;
    bool _initialized;
    
public:
    MySensor(int pin) {
        _pin = pin;
        _initialized = false;
    }
    
    void begin() {
        pinMode(_pin, INPUT);
        _initialized = true;
    }
    
    int read() {
        if (!_initialized) return -1;
        return analogRead(_pin);
    }
};
```

**Flowcode Equivalent (no instance handling needed):**
```xml
<variables>
  <!-- These will automatically become _pin_1, _pin_2, etc. for each instance -->
  <variable public='0'>
    <def name='_pin' type='u8' description='Sensor pin number'
         isconst='0' isHidden='0' isinit='0' usrinit='0' setinit='' />
  </variable>
  
  <variable public='0'>
    <def name='_initialized' type='b1' description='Initialization flag'
         isconst='0' isHidden='0' isinit='0' usrinit='0' setinit='' />
  </variable>
</variables>

<apis>
  <!-- This will automatically become FC_MySensor_Initialise_1(), FC_MySensor_Initialise_2(), etc. -->
  <api name='Initialise' alt='FC_MySensor_$(macro)_$(instance)' type='5' proto='1' />
  <api name='Read' alt='FC_MySensor_$(macro)_$(instance)' type='5' proto='1' />
</apis>
```

**Key Points:**
1. **No pointers needed** - Flowcode handles instance isolation automatically
2. **No object constructors** - Use `Ev_Initialise` event handler instead
3. **Direct variable access** - Access variables directly, not through `this->` or `->`
4. **Instance numbers in code** - Use `$(instance)` in API `alt` attributes to include instance numbers in generated code

#### What Gets Instance-Appended

- **All variables** in the `<variables>` section
- **All API function names** (via the `alt` attribute with `$(instance)`)
- **All properties** (automatically scoped per instance)

#### What Does NOT Get Instance-Appended

- **Local variables** in macros (these are function-scoped)
- **Parameters** in macros (these are function-scoped)
- **Constants** (if truly constant across all instances)

### Converting Arduino Variables to Flowcode Variables

**Arduino Library Example:**
```cpp
class MySensor {
private:
    int sensorPin;
    bool initialized;
    static const int MAX_SAMPLES = 100;
    
public:
    int lastReading;
};
```

**Flowcode Variable Equivalent:**
```xml
<variables>
  <!-- Private variables - will become sensorPin_1, sensorPin_2, etc. automatically -->
  <variable public='0'>
    <def name='sensorPin' type='u8' description='Sensor pin number' 
         isconst='0' isHidden='0' isinit='0' usrinit='0' setinit='' />
  </variable>
  
  <variable public='0'>
    <def name='initialized' type='b1' description='Initialization flag'
         isconst='0' isHidden='0' isinit='0' usrinit='0' setinit='' />
  </variable>
  
  <!-- Public constant - same value for all instances -->
  <variable public='1'>
    <def name='MAX_SAMPLES' type='s16' description='Maximum samples'
         isconst='1' isHidden='0' isinit='1' usrinit='100' setinit='100' />
  </variable>
  
  <!-- Public variable - will become lastReading_1, lastReading_2, etc. automatically -->
  <variable public='1'>
    <def name='lastReading' type='s16' description='Last sensor reading'
         isconst='0' isHidden='0' isinit='0' usrinit='0' setinit='' />
  </variable>
</variables>
```

**Important:** When converting, simply remove the class structure and pointer dereferencing. Flowcode will automatically handle multiple instances by appending instance numbers to variable names during code generation.

---

## 3. Macros Section

The `<macros>` section contains the actual functional code implementation. Each macro corresponds to an API function and contains the flowcode logic (visual programming blocks) that implements that function.

### Macro Structure

```xml
<macros>
  <macro>
    <flowline name='FunctionName' description='Function description' statediag='0'>
      <return name='Return' type='ReturnType' description='Return description' />
      <param name='ParamName' type='ParamType' description='Parameter description' />
      <local name='LocalVar' type='LocalType' description='Local variable description' />
      
      <!-- Flowcode commands go here -->
      <command class_type='calculation' title='Calculation'>
        <exp exp='Variable = Value' />
      </command>
      
      <command class_type='call' title='Call Macro' macro='OtherMacro' />
      
      <command class_type='decision' title='Decision' exp='Condition' swap='0'>
        <flowline>
          <!-- True branch -->
        </flowline>
        <flowline>
          <!-- False branch -->
        </flowline>
      </command>
    </flowline>
  </macro>
</macros>
```

### Macro Elements

#### Return Value
```xml
<return name='Return' type='u16' description='Return value description' 
        isconst='0' isHidden='0' isinit='0' usrinit='0' setinit='' />
```

#### Parameters
```xml
<param name='Channel' type='u8' description='Channel number' 
       isconst='0' isHidden='0' isinit='0' usrinit='0' setinit='' />
```

#### Local Variables
```xml
<local name='temp' type='u16' description='Temporary variable'
       isconst='0' isHidden='0' isinit='0' usrinit='0' setinit='' />
```

#### Command Types

1. **Calculation** - Assign values, perform math operations
```xml
<command class_type='calculation' title='Calculation'>
  <exp exp='result = value1 + value2' />
  <exp exp='counter = counter + 1' />
</command>
```

2. **Call Macro** - Call another macro/function
```xml
<command class_type='call' title='Call Macro' macro='HelperFunction' />
```

3. **Decision** - Conditional branching (if/else)
```xml
<command class_type='decision' title='Decision' exp='value > 100' swap='0'>
  <flowline>
    <!-- True branch -->
  </flowline>
  <flowline>
    <!-- False branch -->
  </flowline>
</command>
```

4. **Loop** - Iteration
```xml
<command class_type='loop' title='Loop' type='0' exp='i < 10'>
  <flowline>
    <!-- Loop body -->
  </flowline>
</command>
```

5. **Switch** - Multi-way branching (switch/case)
```xml
<command class_type='switch' title='Switch' exp='VariableName'>
  <!-- IMPORTANT: Default case MUST be first (no exp attribute) -->
  <case>
    <flowline>
      <!-- Default case code -->
    </flowline>
  </case>
  <!-- Numbered cases follow -->
  <case exp='1'>
    <flowline>
      <!-- Case 1 code -->
    </flowline>
  </case>
  <case exp='2'>
    <flowline>
      <!-- Case 2 code -->
    </flowline>
  </case>
</command>
```

**Critical Rules for Switch Statements:**

1. **Default case must be FIRST**: The default case (without `exp` attribute) must appear before all numbered cases. This is a Flowcode XML requirement.

2. **Use decimal values**: Case expressions must use decimal numbers, not hex. Convert `0x04` to `4`, `0x16` to `22`, etc.

3. **Always include a default case**: Every switch statement should have a default case to handle unexpected values.

**Correct Switch Example:**
```xml
<command class_type='switch' title='Switch' exp='DeviceType'>
  <!-- Default case FIRST -->
  <case>
    <flowline>
      <command class_type='calculation' title='Calculation'>
        <exp exp='.Return = 0' />
      </command>
    </flowline>
  </case>
  <!-- Numbered cases follow -->
  <case exp='1'>
    <flowline>
      <command class_type='calculation' title='Calculation'>
        <exp exp='MemorySize = 4096' />
      </command>
    </flowline>
  </case>
  <case exp='2'>
    <flowline>
      <command class_type='calculation' title='Calculation'>
        <exp exp='MemorySize = 16384' />
      </command>
    </flowline>
  </case>
</command>
```

**Incorrect Switch Example (will cause "attribute exp is not found" error):**
```xml
<!-- WRONG: Default case at the end -->
<command class_type='switch' title='Switch' exp='DeviceType'>
  <case exp='1'>
    <!-- Case 1 -->
  </case>
  <case exp='2'>
    <!-- Case 2 -->
  </case>
  <case>  <!-- ERROR: Default case should be first -->
    <!-- Default -->
  </case>
</command>

<!-- WRONG: Using hex values -->
<command class_type='switch' title='Switch' exp='ProductID'>
  <case exp='0x04'>  <!-- ERROR: Use decimal 4 instead -->
    <!-- Case code -->
  </case>
</command>
```

6. **Simulation** - Simulation-only code
```xml
<command class_type='sim' title='Simulation' macro='Component.Property.GetValue'>
  <return exp='.Return' />
  <argument exp='this' />
  <argument exp='PropertyName' />
</command>
```

### Code Block Structure and Common Errors

#### Variable Initialization

**Always initialize variables before use**, especially return values and loop counters:

```xml
<!-- Good: Initialize return value -->
<command class_type='calculation' title='Calculation'>
  <exp exp='.Return = 0' />
</command>

<!-- Good: Initialize loop counter -->
<command class_type='calculation' title='Calculation'>
  <exp exp='.Idx = 0' />
</command>
<command class_type='loop' title='Loop' type='0' exp='.Idx < 10'>
  <flowline>
    <command class_type='calculation' title='Calculation'>
      <exp exp='.Idx = .Idx + 1' />
    </command>
  </flowline>
</command>
```

#### Decision Blocks (if/else)

Decision blocks require two `<flowline>` elements - one for true, one for false:

```xml
<command class_type='decision' title='Decision' exp='Condition' swap='0'>
  <flowline>
    <!-- True branch - always include, even if empty -->
  </flowline>
  <flowline>
    <!-- False branch - always include, even if empty -->
  </flowline>
</command>
```

**Common Error**: Missing `<flowline>` elements will cause XML parsing errors.

#### Switch Statement Structure

Switch statements have **strict requirements** that must be followed:

1. **Default case MUST be first**: The `<case>` without an `exp` attribute must appear before all numbered cases.

2. **Use decimal values**: Case expressions must use decimal numbers. Hex values like `0x04` will cause errors - use `4` instead.

3. **Always include default case**: Every switch should have a default case to handle unexpected values.

**Correct Structure:**
```xml
<command class_type='switch' title='Switch' exp='DeviceType'>
  <!-- Default case FIRST -->
  <case>
    <flowline>
      <command class_type='calculation' title='Calculation'>
        <exp exp='.Return = 0' />
      </command>
    </flowline>
  </case>
  <!-- Numbered cases follow -->
  <case exp='1'>
    <flowline>
      <!-- Case 1 code -->
    </flowline>
  </case>
  <case exp='2'>
    <flowline>
      <!-- Case 2 code -->
    </flowline>
  </case>
</command>
```

**Common Errors:**

- **"attribute exp is not found"**: Usually caused by:
  - Default case not being first
  - Using hex values (`0x04`) instead of decimal (`4`)
  - Missing closing `</command>` tag for the switch

- **Switch not working correctly**: Check that:
  - All cases have `<flowline>` elements
  - Case values match the variable type (u8, u16, etc.)
  - Default case handles unexpected values

#### Nested Code Blocks

When nesting decision blocks, loops, or switches, ensure proper closing tags:

```xml
<command class_type='decision' title='Outer Decision' exp='Condition1' swap='0'>
  <flowline>
    <command class_type='decision' title='Inner Decision' exp='Condition2' swap='0'>
      <flowline>
        <!-- Inner true -->
      </flowline>
      <flowline>
        <!-- Inner false -->
      </flowline>
    </command>
  </flowline>
  <flowline>
    <!-- Outer false -->
  </flowline>
</command>
```

#### Calling Macros with Return Values

When calling a macro that returns a value, use the `<return>` element:

```xml
<command class_type='call' title='User Macro' macro='GetMemorySize'>
  <return exp='.MemorySize' />
</command>
```

Or assign directly in a calculation:

```xml
<command class_type='call' title='User Macro' macro='GetAddressBits'>
  <return exp='.AddrBits' />
</command>
<command class_type='calculation' title='Calculation'>
  <exp exp='.LocalVar = .AddrBits' />
</command>
```

#### Local Variable Declaration Order

Local variables must be declared **before** they are used in commands:

```xml
<flowline name='MyFunction' description='' statediag='0'>
  <return name='Return' type='u8' description='' />
  <!-- Local variables declared first -->
  <local name='Temp' type='u8' description='' isconst='0' isHidden='0' isinit='0' usrinit='0' setinit='' />
  <local name='Idx' type='u16' description='' isconst='0' isHidden='0' isinit='0' usrinit='0' setinit='' />
  
  <!-- Then commands that use them -->
  <command class_type='calculation' title='Calculation'>
    <exp exp='.Temp = 0' />
    <exp exp='.Idx = 0' />
  </command>
</flowline>
```

### Converting Arduino Code to Macros

**Arduino Library Example:**
```cpp
int MySensor::read() {
    if (!initialized) {
        return -1;  // Error: not initialized
    }
    
    int value = analogRead(sensorPin);
    lastReading = value;
    return value;
}
```

**Flowcode Macro Equivalent:**
```xml
<macro>
  <flowline name='Read' description='Read sensor value' statediag='0'>
    <return name='Return' type='s16' description='Sensor reading or -1 on error' />
    
    <!-- Check if initialized -->
    <command class_type='decision' title='Decision' exp='initialized' swap='0'>
      <flowline>
        <!-- True: Read sensor -->
        <command class_type='call' title='Call Macro' macro='FC_CAL_ADC_Sample'>
          <return exp='.Return' />
          <argument exp='sensorPin' />
        </command>
        
        <!-- Store last reading -->
        <command class_type='calculation' title='Calculation'>
          <exp exp='lastReading = .Return' />
        </command>
      </flowline>
      <flowline>
        <!-- False: Return error -->
        <command class_type='calculation' title='Calculation'>
          <exp exp='.Return = -1' />
        </command>
      </flowline>
    </command>
  </flowline>
</macro>
```

---

## 4. Properties Section

Properties define the configurable options for your component (like pin selection, baud rate, etc.).

### Property Structure

```xml
<properties>
  <property name='PropertyName' 
            target='TargetVariable' 
            typeid='TypeID' 
            hidden='0' 
            locked='0' 
            info='Description text'
            filter='000Option1
001Option2' 
            expansion='MACRO_$(value)' 
            initialiser='($(value))' />
</properties>
```

### Property Attributes

- **`name`**: Display name shown to users
- **`target`**: Variable name that stores the value
- **`typeid`**: Property type:
  - `5` = Pin selection
  - `7` = Boolean (Yes/No)
  - `10` = String
  - `14` = Integer number
  - `16` = Dropdown list
  - `21` = Unsigned integer
- **`hidden`**: `0` = visible, `1` = hidden
- **`locked`**: `0` = editable, `1` = read-only
- **`info`**: Tooltip/help text
- **`filter`**: Options for dropdown (format: `000Value1\n001Value2`)
- **`expansion`**: Macro expansion template
- **`initialiser`**: Initialization code template

### Example Properties

```xml
<properties>
  <!-- Pin selection property -->
  <property name='Sensor Pin' 
            target='SENSOR_PIN' 
            typeid='5' 
            hidden='0' 
            locked='0' 
            info='Select the analog pin for the sensor' />
  
  <!-- Boolean property -->
  <property name='Enable Filter' 
            target='USE_FILTER' 
            typeid='7' 
            hidden='0' 
            locked='0' 
            info='Enable digital filtering of readings' />
  
  <!-- Dropdown property -->
  <property name='Sample Rate' 
            target='SAMPLE_RATE' 
            typeid='16' 
            hidden='0' 
            locked='0' 
            info='Sampling rate in Hz'
            filter='00010 Hz
001100 Hz
0021000 Hz' />
</properties>
```

---

## 5. Events Section

Events are system callbacks that your component can respond to.

### Common Events

```xml
<events>
  <!-- Component initialization -->
  <event class='Components' event='Initialise' target='Ev_Initialise' />
  
  <!-- Property changed -->
  <event class='Components' event='Property' target='Ev_Property_Change' />
  
  <!-- Chip/target changed -->
  <event class='Connection' event='ChipChange' target='Ev_ChipChange' />
  
  <!-- Compile-time events -->
  <event class='Compile' event='AddHeader' target='Ev_AddHeader' />
  <event class='Compile' event='AddProperty' target='Ev_AddProperty' />
  <event class='Compile' event='Start' target='Ev_CompStart' />
  <event class='Compile' event='Stop' target='Ev_CompStop' />
  
  <!-- Simulation events -->
  <event class='Simulation' event='Start' target='Ev_Start' />
  <event class='Simulation' event='Stop' target='Ev_Stop' />
  
  <!-- Timer events -->
  <event class='System' event='Timer' target='Ev_Timer' />
</events>
```

Each event requires a corresponding macro with the same name (e.g., `Ev_Initialise`, `Ev_Property_Change`).

---

## Converting Arduino Libraries to Flowcode Components

### Step-by-Step Conversion Process

#### Step 1: Analyze the Arduino Library

Identify:
- **Public functions** → APIs (type 1 or 5)
- **Private functions** → APIs (type 0) or internal macros
- **Member variables** → Variables (public or private)
- **Constants** → Variables with `isconst='1'`
- **Configuration options** → Properties

#### Step 2: Create the Component Definition

```xml
<definition guid='generate-new-guid' 
            vstate='40' 
            vmin='0' 
            vmaj='1' 
            srcleaf='MyComponent.fcfx' 
            visiblename='My Component' 
            description='Description of what the component does'
            category='Sensors' 
            author='Your Name' 
            manuname='Your Company' 
            manucode='YOUR' 
            embeddedCompatible='1' 
            showmacros='1' 
            iconpath='..\icons\components\sensor.png' />
```

#### Step 3: Map Arduino Functions to APIs

**Arduino:**
```cpp
class DHT22 {
public:
    void begin(int pin);
    float readTemperature();
    float readHumidity();
    bool read();
};
```

**Flowcode APIs:**
```xml
<apis>
  <api name='Initialise' alt='FC_DHT22_$(macro)_$(instance)' type='5' proto='1' />
  <api name='ReadTemperature' alt='FC_DHT22_$(macro)_$(instance)' type='5' proto='1' />
  <api name='ReadHumidity' alt='FC_DHT22_$(macro)_$(instance)' type='5' proto='1' />
  <api name='Read' alt='FC_DHT22_$(macro)_$(instance)' type='5' proto='1' />
</apis>
```

#### Step 4: Convert Variables

**Important:** Remove all pointer/object instance handling. Flowcode automatically handles multiple instances by appending instance numbers to variable names.

**Arduino (with object instances):**
```cpp
class DHT22 {
private:
    int _pin;
    unsigned long _lastReadTime;
    float _temperature;
    float _humidity;
    
public:
    DHT22(int pin) {
        _pin = pin;
        // ... initialization
    }
};
```

**Flowcode Variables (no instance handling needed):**
```xml
<variables>
  <!-- These variables will automatically become _pin_1, _pin_2, etc. 
       for each component instance - no pointers or object handling required -->
  <variable public='0'>
    <def name='_pin' type='u8' description='Sensor pin' 
         isconst='0' isHidden='0' isinit='0' usrinit='0' setinit='' />
  </variable>
  <variable public='0'>
    <def name='_lastReadTime' type='u32' description='Last read timestamp'
         isconst='0' isHidden='0' isinit='0' usrinit='0' setinit='' />
  </variable>
  <variable public='0'>
    <def name='_temperature' type='f32' description='Last temperature reading'
         isconst='0' isHidden='0' isinit='0' usrinit='0.0' setinit='' />
  </variable>
  <variable public='0'>
    <def name='_humidity' type='f32' description='Last humidity reading'
         isconst='0' isHidden='0' isinit='0' usrinit='0.0' setinit='' />
  </variable>
</variables>
```

**Key Conversion Points:**
- Remove class structure - variables go directly in `<variables>` section
- Remove constructors - use `Ev_Initialise` event handler instead
- Remove `this->` or pointer dereferencing - access variables directly
- Flowcode automatically appends instance numbers (e.g., `_pin_1`, `_pin_2`) during code generation

#### Step 5: Create Properties

```xml
<properties>
  <property name='Data Pin' 
            target='DATA_PIN' 
            typeid='5' 
            hidden='0' 
            locked='0' 
            info='Digital pin connected to DHT22 data line' />
</properties>
```

#### Step 6: Implement Macros

Convert each Arduino function to a Flowcode macro. Use Flowcode's visual programming blocks to replicate the logic.

**Example: Initialise Macro**
```xml
<macro>
  <flowline name='Initialise' description='Initialize DHT22 sensor' statediag='0'>
    <return name='Return' type='v0' />
    <param name='Pin' type='u8' description='Data pin number' />
    
    <!-- Store pin number -->
    <command class_type='calculation' title='Calculation'>
      <exp exp='_pin = .Pin' />
    </command>
    
    <!-- Set pin as output initially -->
    <command class_type='call' title='Call Macro' macro='FC_CAL_Pin_SetDirection'>
      <argument exp='.Pin' />
      <argument exp='1' />  <!-- Output -->
    </command>
    
    <!-- Set pin high -->
    <command class_type='call' title='Call Macro' macro='FC_CAL_Pin_SetOutput'>
      <argument exp='.Pin' />
      <argument exp='1' />  <!-- High -->
    </command>
  </flowline>
</macro>
```

### Conversion Checklist

- [ ] Create component definition with GUID
- [ ] Map all public functions to APIs (type 1 or 5)
- [ ] Map all private functions to APIs (type 0) or internal macros
- [ ] Convert all member variables to Flowcode variables
- [ ] Set appropriate public/private flags
- [ ] Create properties for user configuration
- [ ] Implement macros for each API function
- [ ] Add event handlers (Initialise, Property Change, etc.)
- [ ] Test component in Flowcode

### Common Patterns

#### Pattern 1: Initialization Function
```cpp
// Arduino (with object instance)
class MyComponent {
    int pin;
public:
    void begin(int pin) {
        this->pin = pin;
        pinMode(pin, OUTPUT);
    }
};
```

```xml
<!-- Flowcode - no object instance needed -->
<api name='Initialise' alt='FC_Component_$(macro)_$(instance)' type='5' proto='1' />

<!-- In macro, access variables directly (no 'this->' needed) -->
<command class_type='calculation' title='Calculation'>
  <exp exp='pin = .Pin' />  <!-- Direct access, not this->pin -->
</command>
```

**Note:** The `$(instance)` in the `alt` attribute ensures each instance gets a unique function name (e.g., `FC_Component_Initialise_1`, `FC_Component_Initialise_2`).

#### Pattern 2: Read Function
```cpp
// Arduino
int read();
```

```xml
<!-- Flowcode -->
<api name='Read' alt='FC_Component_$(macro)_$(instance)' type='5' proto='1' />
```

#### Pattern 3: Configuration Function
```cpp
// Arduino
void setMode(int mode);
```

```xml
<!-- Flowcode -->
<api name='SetMode' alt='FC_Component_$(macro)_$(instance)' type='5' proto='1' />
```

Or use a Property instead:
```xml
<property name='Mode' target='MODE' typeid='16' 
          filter='000Mode1
001Mode2' />
```

---

## Best Practices

### 1. Naming Conventions
- Use descriptive names for APIs (e.g., `ReadTemperature` not `Read`)
- Prefix private functions with `Prv_` (e.g., `Prv_CalculateChecksum`)
- Use consistent naming for variables (camelCase or snake_case)

### 2. API Design
- Keep APIs simple and focused on one task
- Use properties for configuration that doesn't change during runtime
- Use APIs for runtime operations
- **Do NOT use pointers or object instances** - Flowcode handles multiple instances automatically
- Always include `$(instance)` in API `alt` attributes for code generation macros (type 5)

### 3. Error Handling
- Return meaningful error codes
- Use constants for error values (public variables with `isconst='1'`)
- Document error conditions in API descriptions

### 4. Code Generation
- Use type 5 APIs for functions that generate embedded code
- Use `alt` attribute to create consistent function names
- Include instance numbers in generated code for multi-instance support

### 5. Documentation
- Provide clear descriptions for all APIs, variables, and properties
- Include usage examples in descriptions
- Document any limitations or requirements

---

## Example: Complete Component Structure

Here's a minimal example showing all sections:

```xml
<root>
  <document>
    <components>
      <component class_type='root' codename='my_component'>
        <!-- Properties -->
        <properties>
          <property name='Pin' target='PIN' typeid='5' 
                    info='Select pin' />
        </properties>
        
        <!-- Default Values -->
        <values>
          <value target='PIN' data='$PORTA.0' />
        </values>
        
        <!-- Events -->
        <events>
          <event class='Components' event='Initialise' target='Ev_Initialise' />
        </events>
        
        <!-- APIs -->
        <apis>
          <api name='Read' alt='FC_MyComponent_$(macro)_$(instance)' 
               type='5' proto='1' />
        </apis>
        
        <!-- Variables -->
        <variables>
          <variable public='0'>
            <def name='value' type='u16' description='Read value'
                 isconst='0' isHidden='0' isinit='0' usrinit='0' setinit='' />
          </variable>
        </variables>
        
        <!-- Macros -->
        <macros>
          <macro>
            <flowline name='Read' description='Read sensor value'>
              <return name='Return' type='u16' />
              <!-- Implementation here -->
            </flowline>
          </macro>
          
          <macro>
            <flowline name='Ev_Initialise' description='Initialize component'>
              <return name='Return' type='u32' />
              <!-- Initialization code here -->
            </flowline>
          </macro>
        </macros>
      </component>
    </components>
  </document>
</root>
```

---

## 6. Embedded Components and Component References

Flowcode components can embed other components to handle low-level functionality. This is particularly useful when converting Arduino libraries that use hardware communication protocols.

### Embedded Component Structure

Components can reference other components using `<component class_type='ref'>`. This is commonly used to:
- Embed CAL (Code Abstraction Layer) components for hardware communication (I2C, SPI, UART, etc.)
- Embed utility components (Lookup Tables, Math functions, etc.)
- Embed display components for visualization

**Example from FS3000 Component:**
```xml
<!-- Embedded I2C CAL component for hardware communication -->
<component class_type='ref' guid='ed3a5141-43bb-43e0-86b0-2243fd1147ca' 
           codename='cal_i2c1' ...>
  <!-- I2C component properties and values -->
</component>

<!-- Embedded Lookup Table component for data conversion -->
<component class_type='ref' guid='dfb4d07a-3d70-45d5-83ef-07e3c95d86ab' 
           codename='RawDataLUT' ...>
  <!-- LUT values -->
</component>
```

### Referencing Embedded Component Properties

When embedding components, reference their properties using the `component::property` syntax:

```xml
<properties>
  <!-- Reference embedded component's property -->
  <property name='Channel' target='cal_i2c1::CHANNEL' typeid='16' ... />
  <property name='SDA' target='cal_i2c1::SDA' typeid='5' ... />
</properties>

<values>
  <!-- Set embedded component's property value -->
  <value target='cal_i2c1::CHANNEL' data='001' />
  <value target='cal_i2c1::SDA' data='$PORTD.9' />
</values>
```

### Calling Embedded Component Macros

Call macros from embedded components using the `component` attribute:

```xml
<command class_type='call' title='Component Macro' component='cal_i2c1' macro='Master_Init' />

<command class_type='call' title='Component Macro' component='cal_i2c1' macro='Transaction_Read'>
  <argument exp='.Buff' />
  <argument exp='5' />
</command>
```

### Common Embedded Component Patterns

#### Pattern 1: Hardware Communication (I2C/SPI/UART)
```xml
<!-- Embed CAL component for I2C communication -->
<component class_type='ref' codename='cal_i2c1' ...>
  <!-- I2C configuration -->
</component>

<!-- In macros, use I2C CAL functions -->
<command class_type='call' component='cal_i2c1' macro='Transaction_Read' />
<command class_type='call' component='cal_i2c1' macro='Transaction_Write' />
```

#### Pattern 2: Lookup Tables for Sensor Calibration
```xml
<!-- Embed LUT component for data conversion -->
<component class_type='ref' codename='RawDataLUT' ...>
  <values>
    <value target='intfixed' data='409, 915, 1522, 2066, ...' />
  </values>
</component>

<!-- Use LUT in macros -->
<command class_type='calculation' title='Calculation'>
  <exp exp='value = RawDataLUT::GetInt(.idx)' />
</command>
```

#### Pattern 3: Dynamic Property Updates
Use `Ev_Property` event to update embedded component properties when user changes settings:

```xml
<macro>
  <flowline name='Ev_Property' description='Property changed'>
    <command class_type='decision' title='Decision' exp='Type' swap='0'>
      <flowline>
        <!-- Update LUT based on sensor type -->
        <command class_type='sim' macro='Component.Property.SetValue'>
          <argument exp='RawDataLUT' />
          <argument exp='"intfixed"' />
          <argument exp='"409, 1203, 1597, ..."' />
        </command>
      </flowline>
    </command>
  </flowline>
</macro>
```

### Converting Arduino Libraries with Hardware Communication

When converting Arduino libraries that use I2C, SPI, or UART:

1. **Embed the appropriate CAL component** (e.g., `cal_i2c1` for I2C)
2. **Expose CAL properties** to users through your component's properties
3. **Use CAL macros** in your implementation instead of direct hardware calls
4. **Handle initialization** by calling CAL's initialization macros

**Example: FS3000 I2C Communication**
```xml
<!-- Arduino: Wire.beginTransmission(0x28); Wire.write(...); Wire.endTransmission(); -->

<!-- Flowcode: Use CAL I2C component -->
<command class_type='call' component='cal_i2c1' macro='Transaction_Initialise'>
  <argument exp='0x28' />
</command>
<command class_type='call' component='cal_i2c1' macro='Transaction_Write'>
  <argument exp='.Data' />
  <argument exp='.Length' />
</command>
```

---

## 7. Error Handling and Data Validation

The FS3000 component demonstrates good error handling practices:

### CRC/Checksum Validation

```xml
<macro>
  <flowline name='ReadRaw' description='Read sensor with CRC check'>
    <!-- Read data -->
    <command class_type='call' component='cal_i2c1' macro='Transaction_Read'>
      <argument exp='.Buff' />
      <argument exp='5' />
    </command>
    
    <!-- Calculate checksum -->
    <command class_type='calculation' title='Calculation'>
      <exp exp='.sum = 0' />
      <exp exp='.idx = 1' />
    </command>
    <command class_type='loop' title='Loop' type='0' exp='.idx < 5'>
      <flowline>
        <command class_type='calculation' title='Calculation'>
          <exp exp='.sum = .sum + .Buff[.idx]' />
        </command>
      </flowline>
    </command>
    
    <!-- Validate CRC -->
    <command class_type='decision' title='CRC OK?' exp='.check = 0' swap='0'>
      <flowline>
        <!-- Valid data - process -->
        <command class_type='calculation' title='Calculation'>
          <exp exp='.Return = (.Buff[1] << 8) | .Buff[2]' />
        </command>
      </flowline>
      <flowline>
        <!-- Invalid data - return last known value -->
        <command class_type='calculation' title='CRC Fail'>
          <exp exp='.Return = AirFlowRate' />
        </command>
      </flowline>
    </command>
  </flowline>
</macro>
```

### Range Checking

```xml
<command class_type='decision' title='Decision' exp='AirFlowRate < 409' swap='0'>
  <flowline>
    <!-- Below minimum - return zero -->
    <command class_type='calculation' title='Calculation'>
      <exp exp='.Return = 0' />
    </command>
  </flowline>
  <flowline>
    <command class_type='decision' title='Decision' exp='AirFlowRate > 3686' swap='0'>
      <flowline>
        <!-- Above maximum - return max value -->
        <command class_type='calculation' title='Calculation'>
          <exp exp='.Return = 15.0' />
        </command>
      </flowline>
      <flowline>
        <!-- In range - calculate interpolated value -->
      </flowline>
    </command>
  </flowline>
</command>
```

---

## 8. Lookup Tables and Data Conversion

Many sensors require lookup tables for calibration or unit conversion. Flowcode provides LUT components for this purpose.

### Using Lookup Tables

```xml
<!-- Embed LUT component -->
<component class_type='ref' codename='RawDataLUT' ...>
  <values>
    <value target='intfixed' data='409, 915, 1522, 2066, 2523, 2908, 3256, 3572, 3686' />
    <value target='floatfixed' data='0, 1.07, 2.01, 3.00, 3.97, 4.96, 5.98, 6.99, 7.23' />
    <value target='NumVals' data='9' />
  </values>
</component>

<!-- Use LUT in macros -->
<command class_type='calculation' title='Calculation'>
  <exp exp='raw_value = RawDataLUT::GetInt(.idx)' />
  <exp exp='converted_value = MpsDataLUT::GetFloat(.idx)' />
</command>
```

### Interpolation Between LUT Values

```xml
<!-- Find position in LUT -->
<command class_type='loop' title='Loop' type='2' forvar='.idx' exp='.datapoints'>
  <flowline>
    <command class_type='decision' title='Decision' exp='AirFlowRate > RawDataLUT::GetInt(.idx)' swap='0'>
      <flowline>
        <command class_type='calculation' title='Calculation'>
          <exp exp='.dataposition = .idx' />
        </command>
      </flowline>
    </command>
  </flowline>
</command>

<!-- Calculate interpolation -->
<command class_type='calculation' title='Calculation'>
  <exp exp='.window_size = RawDataLUT::GetInt(.dataposition + 1) - RawDataLUT::GetInt(.dataposition)' />
  <exp exp='.diff = AirFlowRate - RawDataLUT::GetInt(.dataposition)' />
  <exp exp='.percentage_of_window = (FLOAT .diff / FLOAT .window_size)' />
  <exp exp='.window_size_mps = MpsDataLUT::GetFloat(.dataposition + 1) - MpsDataLUT::GetFloat(.dataposition)' />
  <exp exp='.Return = MpsDataLUT::GetFloat(.dataposition) + FLOAT (.window_size_mps * .percentage_of_window)' />
</command>
```

---

## 9. Troubleshooting Common XML Structure Errors

### "attribute exp is not found" Error

This error typically occurs with switch statements and indicates an XML structure problem.

**Common Causes:**

1. **Default case not first in switch statement**
   - **Error**: Default case (`<case>` without `exp`) appears after numbered cases
   - **Fix**: Move default case to be the first case in the switch

2. **Using hex values in case expressions**
   - **Error**: `<case exp='0x04'>` 
   - **Fix**: Use decimal: `<case exp='4'>`
   - **Conversion**: `0x04` = `4`, `0x16` = `22`, `0x64` = `100`, `0x80` = `128`, etc.

3. **Missing closing tags**
   - **Error**: Switch statement not properly closed with `</command>`
   - **Fix**: Ensure every `<command>` has a matching `</command>`

**Example Fix:**

```xml
<!-- BEFORE (causes error) -->
<command class_type='switch' title='Switch' exp='ProductID'>
  <case exp='0x04'>  <!-- ERROR: Hex value -->
    <!-- Case code -->
  </case>
  <case>  <!-- ERROR: Default case should be first -->
    <!-- Default -->
  </case>
</command>

<!-- AFTER (correct) -->
<command class_type='switch' title='Switch' exp='ProductID'>
  <case>  <!-- Default case FIRST -->
    <flowline>
      <command class_type='calculation' title='Calculation'>
        <exp exp='.Return = 0' />
      </command>
    </flowline>
  </case>
  <case exp='4'>  <!-- Decimal value -->
    <flowline>
      <!-- Case code -->
    </flowline>
  </case>
</command>
```

### Missing Flowline Elements

Decision blocks require exactly two `<flowline>` elements:

```xml
<!-- CORRECT -->
<command class_type='decision' title='Decision' exp='Condition' swap='0'>
  <flowline>
    <!-- True branch -->
  </flowline>
  <flowline>
    <!-- False branch (can be empty) -->
  </flowline>
</command>

<!-- ERROR: Missing second flowline -->
<command class_type='decision' title='Decision' exp='Condition' swap='0'>
  <flowline>
    <!-- Only one flowline -->
  </flowline>
</command>
```

### Variable Not Initialized

Always initialize variables before use, especially return values:

```xml
<!-- CORRECT -->
<flowline name='MyFunction' description='' statediag='0'>
  <return name='Return' type='u8' description='' />
  <local name='Counter' type='u16' description='' />
  
  <command class_type='calculation' title='Calculation'>
    <exp exp='.Return = 0' />
    <exp exp='.Counter = 0' />
  </command>
  <!-- Use variables here -->
</flowline>

<!-- ERROR: Using uninitialized variable -->
<flowline name='MyFunction' description='' statediag='0'>
  <return name='Return' type='u8' description='' />
  <!-- Missing initialization -->
  <command class_type='calculation' title='Calculation'>
    <exp exp='.Result = .Return + 1' />  <!-- .Return not initialized -->
  </command>
</flowline>
```

### Local Variable Declaration Order

Local variables must be declared before commands that use them:

```xml
<!-- CORRECT: Variables declared first -->
<flowline name='MyFunction' description='' statediag='0'>
  <return name='Return' type='u8' description='' />
  <local name='Temp' type='u8' description='' />
  <local name='Idx' type='u16' description='' />
  
  <command class_type='calculation' title='Calculation'>
    <exp exp='.Temp = 0' />
  </command>
</flowline>

<!-- ERROR: Variable declared after use -->
<flowline name='MyFunction' description='' statediag='0'>
  <return name='Return' type='u8' description='' />
  
  <command class_type='calculation' title='Calculation'>
    <exp exp='.Temp = 0' />  <!-- ERROR: .Temp not declared yet -->
  </command>
  
  <local name='Temp' type='u8' description='' />  <!-- Too late -->
</flowline>
```

### Switch Statement Best Practices Checklist

When creating switch statements, verify:

- [ ] Default case (`<case>` without `exp`) is the **first** case
- [ ] All case values use **decimal numbers** (not hex like `0x04`)
- [ ] Every case has a `<flowline>` element
- [ ] Switch statement is properly closed with `</command>`
- [ ] Case values match the variable type (u8: 0-255, u16: 0-65535, etc.)

### Debugging Tips

1. **Check XML structure**: Ensure all tags are properly closed
2. **Validate case values**: Convert hex to decimal
3. **Verify default case position**: Must be first
4. **Test with simple cases**: Start with 2-3 cases, then expand
5. **Use linter**: Run `read_lints` tool to catch XML errors early

---

## Summary

Flowcode component source files use XML to define:
- **APIs**: Public and private function interfaces
- **Variables**: Global state and constants
- **Macros**: Visual programming implementation
- **Properties**: User-configurable options
- **Events**: System callback handlers
- **Embedded Components**: References to other components (CAL, LUT, etc.)

Converting Arduino libraries involves:
1. Mapping functions → APIs
2. Mapping variables → Variables section
3. Mapping configuration → Properties
4. Implementing logic → Macros
5. Adding event handlers → Events
6. Embedding CAL components for hardware communication (I2C/SPI/UART)
7. Using LUT components for sensor calibration/conversion
8. Implementing error handling (CRC, range checking)

This structure allows Flowcode to generate both embedded C code and simulation code from the same component definition.

### Key Patterns from Real-World Conversion (FS3000 Example)

Based on the SparkFun FS3000 Arduino Library conversion ([GitHub](https://github.com/sparkfun/SparkFun_FS3000_Arduino_Library)):

1. **Embedded I2C CAL Component**: Uses `cal_i2c1` for all I2C communication
2. **Lookup Tables**: Uses LUT components for raw-to-converted value mapping
3. **CRC Validation**: Implements checksum validation in `ReadRaw` macro
4. **Property-Based Configuration**: Sensor type selection updates LUT values via `Ev_Property`
5. **Unit Conversion**: Provides multiple read functions (`ReadMetersPerSecond`, `ReadMilesPerHour`) that call each other
6. **Range Checking**: Validates sensor readings against minimum/maximum values
7. **Interpolation**: Calculates values between LUT entries for smooth conversion

