# Arduino Library to Flowcode Component Conversion Worksheet

Use this worksheet to systematically convert an Arduino library into a Flowcode component.

## Step 1: Library Analysis

### Library Information
- **Library Name**: _______________________
- **Author**: _______________________
- **Purpose**: _______________________
- **Main Class Name**: _______________________

### ⚠️ Important: Instance Handling
**Note:** Arduino libraries use object instances/pointers to avoid variable conflicts. Flowcode handles this automatically - you do NOT need to:
- Create object instances
- Use pointers (`->`, `this->`)
- Manage instance data manually

Flowcode automatically appends instance numbers to all variables and functions (e.g., `variable_1`, `variable_2`, `FC_Component_Function_1()`, `FC_Component_Function_2()`).

### Public Functions (→ APIs)
| Arduino Function | Return Type | Parameters | Flowcode API Name | API Type |
|-----------------|-------------|------------|-------------------|----------|
| | | | | |
| | | | | |
| | | | | |

### Private Functions (→ Private APIs or Internal Macros)
| Arduino Function | Return Type | Parameters | Flowcode Name | Type |
|-----------------|-------------|------------|---------------|------|
| | | | | |
| | | | | |

### Member Variables (→ Variables)
**Note:** Remove all `this->` or pointer dereferencing. Variables will automatically get instance numbers appended (e.g., `sensorPin_1`, `sensorPin_2`).

| Arduino Variable | Type | Public/Private | Flowcode Name | Flowcode Type | Public Flag |
|-----------------|------|----------------|---------------|---------------|-------------|
| | | | | | |
| | | | | | |

### Constants (→ Public Variables with isconst='1')
| Arduino Constant | Value | Flowcode Name | Flowcode Type |
|-----------------|-------|---------------|---------------|
| | | | |
| | | | |

### Configuration Options (→ Properties)
| Option Name | Type | Options/Values | Property Name | TypeID |
|------------|------|----------------|---------------|--------|
| | | | | |
| | | | | |

---

## Step 2: Component Definition

```xml
<definition guid='_______________________' 
            vstate='40' 
            vmin='0' 
            vmaj='1' 
            srcleaf='_______________________.fcfx' 
            visiblename='_______________________' 
            description='_______________________'
            category='_______________________' 
            author='_______________________' 
            manuname='_______________________' 
            manucode='_______________________' 
            embeddedCompatible='1' 
            showmacros='1' 
            iconpath='..\icons\components\_______________________.png' />
```

---

## Step 3: APIs Section

```xml
<apis>
  <!-- Copy from table above -->
</apis>
```

**Template for each API:**
```xml
<api name='FunctionName' alt='FC_ComponentName_$(macro)_$(instance)' type='5' proto='1' />
```

---

## Step 4: Variables Section

```xml
<variables>
  <!-- Copy from tables above -->
</variables>
```

**Template for each variable:**
```xml
<variable public='0'>
  <def class_type='variable' 
       name='variableName' 
       type='u8' 
       description='Description'
       isconst='0' 
       isHidden='0' 
       isinit='0' 
       usrinit='0' 
       setinit='' />
</variable>
```

---

## Step 5: Properties Section

```xml
<properties>
  <!-- Copy from table above -->
</properties>
```

**Template for each property:**
```xml
<property name='Property Name' 
          target='PROPERTY_VAR' 
          typeid='14' 
          hidden='0' 
          locked='0' 
          info='Description' />
```

---

## Step 6: Values Section

```xml
<values>
  <!-- Default values for each property -->
  <value target='PROPERTY_VAR' data='default_value' />
</values>
```

---

## Step 7: Events Section

```xml
<events>
  <event class='Components' event='Initialise' target='Ev_Initialise' />
  <event class='Components' event='Property' target='Ev_Property_Change' />
  <event class='Connection' event='ChipChange' target='Ev_ChipChange' />
</events>
```

---

## Step 8: Macro Implementation Plan

For each API function, plan the implementation:

### Function: _______________________

**Purpose**: _______________________

**Parameters**:
- `param1` (type): _______________________
- `param2` (type): _______________________

**Return Value**: _______________________

**Logic Steps**:
1. _______________________
2. _______________________
3. _______________________
4. _______________________

**Flowcode Commands Needed**:
- [ ] Calculation blocks
- [ ] Call macros
- [ ] Decision blocks
- [ ] Loop blocks
- [ ] Simulation blocks

---

## Step 9: Code Conversion Examples

### Example 1: Simple Read Function

**Arduino Code:**
```cpp
int read() {
    return analogRead(pin);
}
```

**Flowcode Macro:**
```xml
<macro>
  <flowline name='Read' description='Read analog value'>
    <return name='Return' type='s16' />
    <command class_type='call' title='Call Macro' macro='FC_CAL_ADC_Sample'>
      <return exp='.Return' />
      <argument exp='pin' />
    </command>
  </flowline>
</macro>
```

### Example 2: Function with Error Checking

**Arduino Code:**
```cpp
bool initialize(int pin) {
    if (pin < 0 || pin > 13) {
        return false;
    }
    sensorPin = pin;
    pinMode(pin, INPUT);
    initialized = true;
    return true;
}
```

**Flowcode Macro:**
```xml
<macro>
  <flowline name='Initialise' description='Initialize sensor'>
    <return name='Return' type='b1' />
    <param name='Pin' type='u8' />
    
    <!-- Check pin range -->
    <command class_type='decision' title='Decision' exp='(.Pin < 0) OR (.Pin > 13)' swap='0'>
      <flowline>
        <!-- Invalid pin -->
        <command class_type='calculation' title='Calculation'>
          <exp exp='.Return = 0' />
        </command>
      </flowline>
      <flowline>
        <!-- Valid pin -->
        <command class_type='calculation' title='Calculation'>
          <exp exp='sensorPin = .Pin' />
        </command>
        <command class_type='call' title='Call Macro' macro='FC_CAL_Pin_SetDirection'>
          <argument exp='.Pin' />
          <argument exp='0' />  <!-- Input -->
        </command>
        <command class_type='calculation' title='Calculation'>
          <exp exp='initialized = 1' />
          <exp exp='.Return = 1' />
        </command>
      </flowline>
    </command>
  </flowline>
</macro>
```

### Example 3: Function with Loop

**Arduino Code:**
```cpp
void sendArray(uint8_t* data, int length) {
    for (int i = 0; i < length; i++) {
        Serial.write(data[i]);
    }
}
```

**Flowcode Macro:**
```xml
<macro>
  <flowline name='SendArray' description='Send byte array'>
    <return name='Return' type='v0' />
    <param name='Data' type='T8*' />
    <param name='Length' type='s16' />
    <local name='i' type='s16' />
    
    <command class_type='calculation' title='Calculation'>
      <exp exp='.i = 0' />
    </command>
    <command class_type='loop' title='Loop' type='0' exp='.i < .Length'>
      <flowline>
        <command class_type='call' title='Call Macro' macro='Send'>
          <argument exp='.Data[.i]' />
        </command>
        <command class_type='calculation' title='Calculation'>
          <exp exp='.i = .i + 1' />
        </command>
      </flowline>
    </command>
  </flowline>
</macro>
```

---

## Step 10: Testing Checklist

### Component Structure
- [ ] Component definition complete
- [ ] All APIs defined
- [ ] All variables defined
- [ ] All properties defined
- [ ] Default values set
- [ ] Events declared

### Implementation
- [ ] All API macros implemented
- [ ] Event handler macros implemented
- [ ] Error handling included
- [ ] Comments/documentation added

### Testing
- [ ] Component loads in Flowcode
- [ ] Properties visible and editable
- [ ] APIs appear in function list
- [ ] Code compiles for target
- [ ] Simulation works
- [ ] Functionality matches Arduino library

---

## Step 11: Common Conversion Patterns

### Pattern: Constructor → Ev_Initialise
```cpp
// Arduino (with object instance)
MyClass(int pin) {
    this->pin = pin;
    pinMode(pin, OUTPUT);
}
```
```xml
<!-- Flowcode - no object instance needed -->
<macro>
  <flowline name='Ev_Initialise'>
    <!-- Access variables directly, not through this-> -->
    <command class_type='calculation' title='Calculation'>
      <exp exp='pin = PropertyValue' />  <!-- Direct access -->
    </command>
    <!-- Initialization code -->
  </flowline>
</macro>
```

**Key Difference:** Remove `this->` - access variables directly. Flowcode automatically handles instance isolation.

### Pattern: Getter Function → Property or GetValue API
```cpp
// Arduino
int getPin() {
    return pin;
}
```
```xml
<!-- Option 1: Use property directly -->
<!-- Option 2: Create GetValue API -->
<api name='GetValue' alt='' type='2' proto='1' />
```

### Pattern: Setter Function → SetValue API or Property
```cpp
// Arduino
void setPin(int pin) {
    this->pin = pin;
}
```
```xml
<!-- Option 1: Use property -->
<!-- Option 2: Create SetValue API -->
<api name='SetValue' alt='' type='2' proto='1' />
```

### Pattern: Status Check → Boolean Return API
```cpp
// Arduino
bool isReady() {
    return ready;
}
```
```xml
<api name='IsReady' alt='FC_Component_$(macro)_$(instance)' type='5' />
<return name='Return' type='b1' />
```

---

## Notes and Observations

**Arduino Library Specifics:**
- _______________________
- _______________________
- _______________________

**Flowcode Implementation Notes:**
- _______________________
- _______________________
- _______________________

**Challenges Encountered:**
- _______________________
- _______________________
- _______________________

**Solutions Applied:**
- _______________________
- _______________________
- _______________________

---

## Final Checklist

Before considering the conversion complete:

- [ ] All functions converted
- [ ] All variables mapped
- [ ] Properties configured
- [ ] Macros implemented
- [ ] Event handlers added
- [ ] Documentation complete
- [ ] Component tested
- [ ] Code reviewed
- [ ] Ready for release

---

## Additional Resources

- See `Flowcode_Component_Source_Documentation.md` for detailed documentation
- See `Flowcode_Component_Quick_Reference.md` for quick lookup tables
- Reference existing components in `CAL_Source/` and `IO_Source/` folders

