# Flowcode 11 Component Creation — Confirmed Schema Reference

**Terminology correction (confirmed via the Flowcode wiki's own
"Component Configuration" page — https://www.flowcode.co.uk/wiki/index.php?title=Component_Configuration):
there is no separate "Component Builder" tool.** What actually exists:
you build a normal Flowcode project, with the component root (Panel)
selected, then go to **File > Export** (left-hand nav). That opens a
"Project information" screen with a **"Component export"** panel on the
right containing two separate tiles — confirmed via a real screenshot:
- **"Edit the export settings for your component"** — opens the three
  real, named managers below. Use this one for anything covered in this
  document.
- **"Export this project as a component"** — performs the actual export/
  build step (produces the `.fcfx` component file). A different action,
  not where the managers live.

Clicking **"Edit the export settings for your component"** is what opens
the three managers:

- **Settings Manager** — wraps the project into a component: Name,
  Version, Cosmetic Name, Category, Icon, Author, Description, Keywords,
  plus advanced options (GUID, dynamic loading, macro inheritance, unit
  scale).
- **Interface Manager** — exposes the project's macros and constants:
  macro types are Hidden, Downloadable, Simulation, Hidden Embedded, and
  Embedded; constants are Private or Public; variables can be filtered to
  choose which become public.
- **Resource Manager** — packages external files (meshes, bitmaps, etc.)
  into the component.

So the full path to reach any of the three managers is: **File > Export
> "Edit the export settings for your component"**. There is no separate
builder window outside of that. This project's actual work has been
direct `.fcfx` XML editing
(reading/writing the exported file format itself) rather than driving
those three managers through the UI — that's a legitimate way to produce
the same result, but it's worth being precise that it's XML-level editing
of a real Flowcode project, not use of some distinct "Component Builder"
product. It is also, per the person running this project, genuinely
difficult — most Flowcode users never do this, which is part of why
getting the schema details exactly right (rather than guessed) matters as
much as it has throughout this project.

Guides for this live scattered across the Flowcode wiki rather than in
one place — the Component Configuration page above is one entry point,
not a complete reference. Simulation behaviour for custom components is
reportedly even harder to get right than the export/schema side covered
here, and is NOT something this document has verified against a real
file — treat anything simulation-related as unconfirmed until checked
the same way everything else in this document was.

Distilled from real, exported `.fcfx` files during the NEC_IR component build
(session history in `NEC_IR_Full_Handover_3.md`). Everything here was
confirmed against an actual file or an actual Flowcode Export result —
nothing in this document is guessed. If you (a future AI, or a future
session) need to build or edit a Flowcode component and this file doesn't
answer the question, get a real exported `.fcfx` file and check rather than
guessing — that discipline is what kept this project's builds actually
working.

## 0. The one methodology rule that matters more than any fact below

**Real file over guessing.** Every claim in this document was checked
against an actual `.fcfx` file the user exported from real Flowcode, or an
actual error message from Flowcode's own Export step. When you don't know
something, say so and ask for a real file/export result rather than
asserting a plausible-sounding answer. This project's history has several
examples of guesses that were subtly wrong (an invented `TimedInterval1`
property, an assumed no-argument `StartCounter`, a "matches the reference
file" panel fix that was actually the wrong rule for an *exported*
component) — all caught only because they were checked against something
real.

## 0.1 Two different audiences: this document vs. the `.fcfx` files it
     describes

**This reference document is written for an AI, not a person, and can be
as dense and technical as needed** — exact attribute names, raw XML
fragments, compiler/linker error text, terse cross-references between
sections. The person driving a build already has the component idea and
the requirements; they don't need this document to teach them Flowcode
concepts, and there's no reason to soften anything here for human
readability.

**The `.fcfx` component files themselves are the opposite** — a real
person, quite possibly a beginner, will read them inside the Flowcode
IDE: property `info=` tooltips, macro/flowline `description=` text,
property/folder display names, variable descriptions. Every one of those
needs to stay clear, plain-language, and approachable regardless of how
technical the underlying XML mechanics are. Concretely: write `info=`
text the way you'd explain the setting to someone who has never seen the
component before (what it does, when to change it, valid range/units if
relevant); write macro `description=` text explaining what the macro
does and when it's called, not implementation trivia; keep public
variable/property display names in plain English rather than internal
codenames. This has already been the practice throughout this project's
real components (see the `info=` text on e.g. the RX Pin, Held Threshold,
and PWM properties in Section 3/11, and macro descriptions throughout
`NEC_IR_v3_IOC.fcfx`) — the rule going forward is to keep doing that
deliberately, not to let it slip because the underlying schema knowledge
in THIS document is dense.

## 1. Top-level `.fcfx` document shape

```
<root>
<document ... target='PIC.16F.16F18877' ...>
  <config .../> <plugins/> <supplement/> <debug/> <traces/> <ghost>...</ghost>
  <components>
    <settings .../>
    <definition guid='...' vmin='..' vmaj='..' srcleaf='...' visiblename='...'
                description='...' category='...' ... iconpath='...' />
    <component class_type='root' codename='...' ...>
      <resources/>
      <properties>...forwarded properties...</properties>
      <values>...root-level forwarded property overrides...</values>
      <events/>
      <apis>...public macro list...</apis>
      <variables>...public + internal variables...</variables>
      <macros>...all macros, public and internal, live in one flat list...</macros>
      <component class_type='ref' guid='...' codename='ChildName' ...>
        ...child component instance (see section 5)...
      </component>
      ...more child components...
    </component>
  </components>
  <scadaresourcelookup/> <keymap/>
  <panel2d.../> <panel3d.../> <panels2d>...</panels2d>
  <layout>...one <view> per macro, for the editor's tab/scroll state...</layout>
</document>
</root>
```

The GUID in `<definition guid='...'>` is the component's permanent identity.
Generate a fresh random GUID for every genuinely NEW component. Keep the
same GUID across revisions of an existing component (only bump `vmaj`).

**`<definition author='...'>` — always ask, never guess or leave blank.**
When building a component from scratch (no existing `.fcfx` to inherit the
attribute from), ask the person "What name would you like to add for the
component developer?" before writing the `<definition>` block, and set
`author='<their answer>'` on it. This mirrors how real Matrix-authored
reference components carry `author='Matrix Ltd'` (Section 8) — it's a
real, meaningful field (Settings Manager's "Author" field per the intro
section above), not a cosmetic placeholder. When editing an EXISTING
component that already has an `author` attribute, leave it as-is unless
the person explicitly asks to change it.

## 2. Property typeid catalog (confirmed)

| typeid | Meaning |
|---|---|
| 5  | Pin selection |
| 6  | Single Analog Pin |
| 7  | Boolean / True-or-False |
| 10 | String |
| 12 | Fixed List Of Text |
| 14 | Signed Integer |
| 15 | Floating Point |
| 16 | Dropdown / filtered list (has a `filter` attribute — see section 3) |
| 17 | Panel Object |
| 18 | Bit Mask |
| 19 | Digital Port Byte |
| 21 | Unsigned Integer |
| 24 | Macro picker (has a `filter` attribute listing candidate macros — see section 3) |
| 25 | Variable |

## 2.1 A plain (non-forwarded, non-child) property NEVER needs a matching
    `<variable>` declaration — confirmed the hard way, correcting an
    earlier wrong assumption in this project

An earlier draft of `PWM_HighRes_Timer1` declared a `<variable name='PwmPinSel'>`
alongside a `<property target='PwmPinSel'>`, on the unconfirmed assumption
(carried over from a different, real forwarded-child pattern - see Section
3) that typeid != 5 properties need an explicit backing variable the way
`typeid='5'` properties famously do NOT. This was wrong, and it caused a
real, reproducible bug: with both a `<property target='X'>` and a
`<variable name='X'>` sharing the identical name `X`, Flowcode's flowchart
expression evaluator resolved `X` to the VARIABLE, not the live property —
so the property's Properties-panel value could change all day and the
variable just sat at its own declared default forever. This was diagnosed
via `Debug.PrintLn` output the user added themselves inside `Ev_Property_Change`,
showing the "read" value never changed no matter what was selected in the
Properties panel — confirmed hard evidence, not a guess.

Definitive proof this pattern is wrong: in `PWM.fcfx`, a large, real,
professionally-authored component with root-level properties `CHANNEL`
(typeid 16), `PORT` (typeid 5), `PERIOD`/`PRESCALE` (typeid 21), `HWALT`
(typeid 7), and others - referenced directly by name throughout hundreds
of lines of Decision/Calculation expressions - the root `<variables>`
element is **completely empty** (`<variables />`). Zero backing variables
exist for ANY property, of any typeid. `Ultrasonic_HC_SR04.fcfx` confirms
the same pattern: its properties (`Type`, `TimingSource`, `OPP`, `ECHO`,
`ClockSpeed`, `DeviceFamily`, etc, spanning typeid 5/7/10/16/21) have no
matching variables either - the only three declared variables (`count`,
`true`, `false`) are genuinely internal runtime state with no property of
the same name.

**The rule, stated plainly**: a property's `target` name IS how you
reference its current value directly inside flowchart expressions
(Calculation, Decision, etc) - no separate `<variable>` element required
or wanted, for ANY typeid. Only declare a `<variable>` for state that has
no corresponding property at all (e.g. this project's own `CurrentDuty`/
`CurrentFrequency`, which track the last-applied runtime values and are
never shown in the Properties panel). Declaring both a property and a
same-named variable does not error at export time - it just silently
breaks the property, which is what makes this bug easy to introduce and
hard to notice without deliberately testing with debug output like the
user did here.

This does NOT contradict the separate, correctly-confirmed rule that
native C code cannot read a property value directly and must go through a
Calculation icon first (see Section 7/ApplyPWM's own comments) - a
Calculation icon CAN read a plain property directly by its target name,
exactly like these real files do; it is only `class_type='native'` C code
that cannot, and that limitation is bridged by copying the property's
value into a genuine local/global variable via a Calculation icon
immediately beforehand - never by declaring a variable with the SAME name
as the property.

## 3. The forwarded-property pattern

A component exposes a child component's internal property at its own
(root) level like this:

```xml
<property name='Displayed Label' target='ChildCodename::childPropertyName'
           typeid='16' hidden='0' locked='0' info='Tooltip text.'
           filter='000OptionA
001OptionB
002OptionC' />
```

- `target='ChildCodename::propName'` is what makes this a *forward* rather
  than a plain property — it points at a live property on a child
  component instance already in `<components>`.
- Properties can be grouped into a folder for the properties panel:
  `<property name='Group Label' folder='ChildCodename::some_id' hidden='0'>...</property>`
  wrapping child `<property>` elements. The `folder` id string itself
  appears to be an arbitrary internal identifier — it doesn't need to match
  anything else, just be present and (ideally) unique per group.
- `locked='1'` makes a forwarded property read-only in the properties
  panel — used for calculated/derived values the user shouldn't hand-edit
  (e.g. `Estimated Best Period`, `Max Time Measurement`).
- A `typeid='16'` (dropdown) forward needs a real `filter` string copied
  from an actual exported file showing that child component's real filter
  list — these are NOT freely inventable per-child; a `TimedInterval`
  component, for example, does NOT expose the same forwardable properties
  as a `Timer` component despite superficial similarity. Confirmed real
  `TimedInterval` forwards: `TimeUnit`, `TimePeriod`, `EstBestPeriod`
  (locked), `MaxTimeMeasurement` (locked), `CallbackMacro` (typeid 24).
  Confirmed real `Timer` forwards: `Timer`, `Prescaler`, `BitDepth`
  (locked), `InstructionRate` (locked), `InstructionTime` (locked),
  `MaxTimeMeasurement` (locked).
- Root-level `<values>` then carries the actual current value for each
  forwarded target, e.g. `<value target='TimedInterval1::TimePeriod'
  data='50' />` — these values are what actually get edited by the
  properties panel; the child component's own `<values>` block is
  typically left empty (`<values />`) and synced from these at
  load/save time.
- A `typeid='24'` (macro picker) forward's `filter` attribute lists
  candidate macros with a two-line-per-entry format:
  `NamMacroName\nDesDescription text`. Set `locked='1'` on a macro-picker
  forward when the macro binding must never be changed by whoever embeds
  the component (e.g. a callback macro wired to an internal state
  machine) — leaving it unlocked invites someone repointing a periodic
  callback away from code that depends on it firing.

## 4. Flowchart command types (confirmed real syntax)

- **Calculation**: `<command class_type='calculation' title='Calculation'><exp exp='X = Y + 1' /></command>`
- **Decision**: exactly two `<flowline>` children (true branch, then false
  branch). The false branch may be empty (`<flowline />`) but must be
  present — omitting it is invalid.
  `<command class_type='decision' title='Decision' exp='X == 1' swap='0'><flowline>...</flowline><flowline /></command>`
- **Loop**: `type='0'` is a while-style loop (`exp` is the continue
  condition, checked before each iteration):
  `<command class_type='loop' title='Loop' type='0' exp='.I < .N' for1='' for3=''><flowline>...</flowline></command>`
  `type='2'` is a for-style loop with a loop variable:
  `<command class_type='loop' title='Loop' type='2' forvar='.I' exp='8' for1='' for3=''><flowline>...</flowline></command>`
- **Call** — internal macro (same component):
  `<command class_type='call' title='Call Macro' macro='SomeMacro'><argument exp='...' /></command>`
  Call — child component macro:
  `<command class_type='call' title='Component Macro' component='ChildCodename' macro='SomeMacro'><argument exp='...' /><return exp='.LocalVar' /></command>`
  A macro call with no arguments and no return value can self-close:
  `<command class_type='call' title='Component Macro' component='Timer1' macro='StopCounter' />`
- **Switch/case**: the default case (no `exp` attribute) must come FIRST,
  before any `exp='N'` cases. Case values are DECIMAL, not hex. No
  fallthrough between cases.
  ```xml
  <command class_type='switch' title='Switch' exp='StateVar'>
    <case><flowline /></case>              <!-- default, must be first -->
    <case exp='0'><flowline>...</flowline></case>
    <case exp='1'><flowline>...</flowline></case>
  </command>
  ```
- **Interrupt binding**: `class_type='interrupt'` can be placed inside any
  macro. `trigger='3'` is shared by both UART and IOC (interrupt-on-change)
  triggers; edge direction is set via `maskhi`/`masklo` bitmask attributes.
  A component that deliberately does NOT own its own external interrupt
  (leaving that to whoever embeds it) simply exposes a plain callable
  macro (e.g. `ProcessEdge()`) and documents that the embedding project's
  own interrupt macro must call it — no `<command class_type='interrupt'>`
  appears in the component's own macros for that path.

## 5. Variable scoping (confirmed via a real Flowcode export error)

- Component-level (root) variables are referenced WITHOUT a leading dot:
  `RxState = 0`
- Macro-local variables, macro parameters, and the macro's own `Return`
  value ALWAYS need a leading dot: `.Elapsed`, `.TargetUs`, `.Return`.
- Getting this backwards produces a real Flowcode error at export/compile
  time — this was confirmed the hard way, not assumed.

## 6. Expression / operator syntax (confirmed against Flowcode's own wiki
   and real exported files)

- Arithmetic: `+ - * /` (and `MOD`/`%` for modulus).
- Bitwise: `AND`/`&`, `OR`/`|`, `XOR`/`^`, `NOT`/`~`, `<<`, `>>`. Both the
  English keyword and the C-style symbol work identically — `AND` and `&`
  are the same bitwise operator, `OR`/`|` the same, etc.
- Logical: `&&`, `||`, `!`. These combine separate true/false conditions
  (e.g. `(RxState == 0) && (IsRepeat == 1)`) — do not confuse with the
  bitwise operators above, which operate on the bits of a single value
  (e.g. `(.Value AND .Mask) != 0` to test one bit of a byte).
- Comparison: `= ==` (equal), `<> !=` (not equal), `< <= > >=`.
- Typecasts are prefix keywords with NO parentheses: `SIGNED expr`,
  `UNSIGNED expr`, `FLOAT expr`. Float literals always need an explicit
  `.0` (e.g. `FLOAT .Raw / 12.0 + 2.0`, not `/ 12`).
- Numeric literals accept decimal, hex (`0x55`), and binary (`0b01010101`).
- Parentheses `( )` work normally for grouping.

## 7. Rules specific to EXPORTING a project as a component

These are NOT relevant to a plain Flowcode project — they matter only once
you use File > Export > "Export this project as a component", and several
of them were learned by actually running that export and reading its real
error output / real resulting behaviour, not from documentation:

- **`class_type='native'` ccode is spliced in 100% verbatim, with zero name
  substitution.** Confirmed by reading a real Flowcode-generated `.c` file
  (`PWM_HighRes_Timer1`, compiled with real `avr-gcc`) after two guessed
  fixes both failed with "undeclared identifier" errors. Flowcode does NOT
  scan native ccode text for flowchart symbol names and rewrite them — the
  text you type is pasted exactly where the command sits in the flowline,
  and nothing more.
  - **Component-level `<variable>`s and properties compile to a name you
    cannot predict or hand-type**: `FCV_<instance-hash>_<codename+instance
    number>__<UPPERCASED_NAME>`, e.g. `FCV_0fd61_PWM_HighRes1__CURRENTFREQUENCY`.
    The `<instance-hash>_<codename+number>` part is assigned per-project,
    per-instance, at the point the end user drops the component onto their
    panel — unknowable and unwritable at component-authoring time. **Native
    ccode can never reference a component-level `<variable>` or a property
    by name, directly, at all** — this goes further than the earlier
    "native C can't read a property, only a genuine variable" rule; it
    can't reliably read a genuine component-level *variable* either.
  - **Macro `<local>`s and `<param>`s compile to a predictable name with NO
    instance-dependent part**: `FCL_<UPPERCASED_NAME>` — e.g. a local
    declared `<local name='PinSelLocal'>` compiles to `FCL_PINSELLOCAL`
    (note the full uppercasing, not just the prefix). Because this has no
    per-instance hash, it's the ONLY thing native ccode can safely
    reference by a hand-typed name.
  - **The fix pattern**: before a native command needs a component-level
    variable's value, copy it into a `<local>` first via an ordinary
    Calculation icon (`.LocalName = ComponentVariable`, readable directly
    since Calculation icons operate in flowchart-space, not C-space), then
    reference that local from native ccode as `FCL_<UPPERCASED_NAME>`.
  - **A `class_type='native'` command whose ccode is itself a full
    function definition (`void helper(...) { ... }`) does NOT escape to
    file/global scope** — it's spliced in exactly where it sits in the
    flowline, which lands it *nested inside* the enclosing macro's
    generated C function. Confirmed AVR-GCC (v7.3, GNU nested-function
    extension) accepts this and compiles/links it successfully, so it is
    not itself an error — just a structural surprise worth knowing about
    if you go looking for the function at file scope and don't find it.

- **Give it a real category.** An empty/default category dumps the
  component into a junk-drawer "Misc" bucket in the component browser.
  Set `category='...'` to match wherever its sibling components already
  live (e.g. `'Wireless'` to sit next to an existing RC5 component).
- **Every child component except the wrapper must be invisible and
  co-located.** All non-wrapper children (e.g. a `PWM`, a `Timer`, a
  `TimedInterval`) need `visible='0'`, `interactive='0'`, and should sit
  at the identical `x`/`y` position (distinguished only by `z` stacking).
  Only the `LibraryComponent1` wrapper (see below) stays `visible='1'`
  and is the thing the embedding user actually sees/positions on their
  panel. Getting this wrong (e.g. matching a *plain project's* real
  component layout, where components ARE meant to be spread out and
  visible) causes visual/panel placement bugs specific to the exported
  component context — confirmed the hard way on this project's `Timer1`.
- **`LibraryComponent1` is a real, load-bearing wrapper child**, not
  optional cosmetic clutter — guid `58be670e-18fb-477e-ab09-61fde14b23ec`.
  It carries no properties/apis/macros of its own; its `<values>` block
  just holds display data, notably `Text::sText` — the label text shown
  on the component's icon/box in the embedding project's panel (set this
  to the component's short display name, e.g. `'NEC IR'`).
- **`<definition description='...'>` can contain real embedded newlines**
  — multi-line descriptions are valid and more readable in Flowcode's own
  component info panel than one long single-line string.
- **Icon**: `<definition iconpath='.\Name.png' />` points at a 24×24 PNG
  bundled with the component. Background MUST be fully transparent
  (alpha channel, not a white/dark fill) — a component viewed under a
  dark Flowcode theme with an opaque icon background looks broken. At
  real list-render size (much smaller than 24×24 on screen — closer to
  12–16px effective), fine detail and thin outlined shapes blur into an
  indistinct blob; bold, simple, high-contrast shapes with a single
  accent colour read far better than detailed multi-tone artwork.
- **Export's own error checker is authoritative for child component API
  signatures** — more so than reading that child's flowchart/macro
  definitions yourself. This project had a case where a `Timer`
  component's `StartCounter` macro was (incorrectly) inferred to take no
  argument from inspecting a different macro's usage pattern; Flowcode's
  real Export error ("Too few arguments: Timer1::StartCounter") was what
  actually settled it. When in doubt about a child component macro's real
  signature, export and read the error, don't just re-inspect the
  flowchart.

## 8. Confirmed child component APIs referenced in this project

**Timer** (guid `24ad2718-c70b-4088-aeda-3949dfdba740`): `StartCounter`
(takes one argument — confirmed via real export error, not zero as
initially assumed from flowchart inspection alone), `StopCounter` (no
args), `ResetCounter` (no args), `GetCountMicroSeconds`,
`GetCountMilliseconds`, `GetCountReal`, `GetCountSeconds`,
`GetCountString`, `GetRawCount` (all no-argument, all return a value).
Safe to call `GetCountMicroSeconds()` repeatedly while the counter is
still running (i.e. before `StopCounter`).

**TimedInterval** (guid `d7633558-54a4-47ff-8c00-95170632c57e`, vmin=2
vmaj=1): fires a user-named callback macro periodically at a fixed `Time
Period`. Public API: `StartTimerInterval` / `StopTimerInterval` (no
arguments). Its own periodic hardware interrupt is entirely internal to
the component — an embedding project does not need to add anything for
it (confirmed: no user-visible interrupt binding appears in a real sample
project using this component).

**PWM** (guid `444fb704-814c-4707-a15c-759ba088505c`): `Enable()`,
`Disable()`, `SetFrequency(u32)`, `ChangePeriod(u16,s16)`,
`SetDutyCycle(u8)`, `SetDutyCycle10Bit(u16)`.

## 9. Component lifecycle events (the `<events>` block) and `sim`-class
   built-in commands

Confirmed from THREE independent sources: two real, professionally-authored
Matrix TSL components (`PWM.fcfx`, `Ultrasonic_HC_SR04.fcfx`), and a blank
component export produced specifically to see Flowcode's own auto-generated
scaffold (via the real "Add event" UI: Project Explorer's Events tree lists
event categories like `Components > Initialise`, `Components > Property`,
`Compile`, `Connection`, `Simulation`, `System`; selecting one and choosing
`<Add new>` opens a "Create a New Macro" dialog pre-filled with a default
macro name and the correct return type already set).

### 9.0 Events run in the simulation/IDE engine, NOT on the embedded target
   — but the property VALUES they set still are

This is a distinction the earlier draft of this document glossed over, and
it matters: `<events>`-bound macros (`Ev_Initialise`, `Ev_Property_Change`,
etc.) execute inside Flowcode's own simulation/IDE engine — they are
design-time behaviour, not code that gets compiled into the firmware that
runs on the real microcontroller. A `sim`-class command like
`Component.Property.SetValue` never appears in generated C output; it only
runs while you're interacting with (or simulating) the component inside
Flowcode itself.

What DOES carry through to the embedded build is the resulting property
VALUE. A property is a stored value in the project file, and once
`Ev_Property_Change` has written that value (by you changing "Output Pin"
in the Properties panel, which fires the event in the IDE), that stored
value is what gets read when the project is compiled/exported — including
by Flowcode's own pin-allocation/pin-conflict system, if it consults
`typeid='5'` properties at compile time. So the mechanism is real and
useful, but for the right reason: not because the event macro "runs on
the chip," but because it deterministically sets a persisted value that
compilation later reads.

Practical consequence for a hidden auto-set property: it depends on you
(or the simulator) actually triggering the Property event at least once
before compiling — which is exactly why `Ev_Initialise` calling
`Ev_Property_Change` once at load time matters, so the hidden property is
correct even if the user never happens to touch "Output Pin" after
dropping the component.

### 9.1 How the binding works

An empty `<events />` is valid (no lifecycle hooks). To bind one, add
`<event class='...' event='...' target='SomeMacroName' />` entries inside
`<events>`, and define a matching macro (any flowchart macro, anywhere in
`<macros>`) whose `<flowline name='SomeMacroName'>` matches the `target`.
**The macro name is NOT magic or reserved** — it's a free-form label you
type into an editable "Name of macro" field. Flowcode suggests a default
name per event type (e.g. `Ev_Property` for the Property event,
`Ev_Initialise` for the Initialise event) but a real shipped component is
free to rename it (`PWM.fcfx` renames the Property-event macro to
`Ev_Property_Change`) — only the `<event target='...'>` attribute has to
match the macro's actual name, the string itself carries no special meaning
to Flowcode.

Confirmed real event bindings seen across the reference files:

```xml
<event class='Components' event='Initialise' target='Ev_Initialise' />
<event class='Components' event='Property' target='Ev_Property_Change' />
<event class='Components' event='Renamed' target='Ev_Renamed' />
<event class='Compile' event='AddHeader' target='Ev_AddHeader' />
<event class='Compile' event='AddInterrupts' target='...' />
<event class='Simulation' event='Start' target='Ev_Initialise' />
<event class='Connection' event='ChipChange' target='Ev_ChipChange' />
<event class='Connection' event='FCDChange' target='Ev_ChipChange' />
<event class='System' event='Timer' target='Ev_Timer' />
```

The Project Explorer's Events tree (see the blank-export screenshot) also
lists further categories not yet confirmed with a real working example:
`Components > Added/Adding/AutoIdEBlock/Deleted/Deleting/Initialising/
PostInitialise/ProjectClosedown/PropertyEx/Removed/Removing/Resize`,
`Console`, `DataRecorder`, `File`, `Graphics`, `Keyboard`, `Mouse`. Treat
these as real (the tree only lists mechanisms Flowcode actually supports)
but unconfirmed in exact usage until seen in a working file.

### 9.2 Confirmed signatures for the two most useful lifecycle events

Both confirmed via a blank component export with literally nothing added
beyond the event binding + auto-generated empty macro shell (so this is
Flowcode's own default, not an authored file's stylistic choice):

- **`Initialise`** — fires once when the component instance is linked to
  its parent (i.e. dropped onto a panel / loaded).
  `<return name='Return' type='u32' description='Non-zero to prevent initialisation' isconst='0' isHidden='0' isinit='0' usrinit='0' setinit='' />`
  The blank auto-generated macro body is completely empty apart from this
  `<return>` — no locals, no auto-inserted calls.
- **`Property`** — fires whenever any property on the component instance
  changes (in the IDE, at design time).
  `<return name='Return' type='u32' description='' isconst='0' isHidden='0' isinit='0' usrinit='0' setinit='' />`
  Same: auto-generated body is empty apart from the `<return>`.
  A real author-written version of this macro (`Ev_Property_Change` in
  `PWM.fcfx`, `Ev_Property` in `Ultrasonic_HC_SR04.fcfx`) is where all the
  dynamic property logic lives — `SetFilter`/`SetValue`/`SetVisible` calls,
  reading `FCD.GetItemValue` for target-device info, etc.
- **Do not guess a `v0` (void) return type for these** — an earlier draft
  in this project did exactly that and it was wrong; both confirmed real
  examples use `u32`, and neither ever explicitly sets a non-zero value
  (so it presumably just defaults to 0/success either way), but the
  declared return TYPE is still part of what Flowcode expects the macro's
  shape to be.

### 9.3 `sim`-class commands (design-time / IDE-only, NOT compiled into firmware)

A new flowchart command type, `class_type='sim'`, calls a built-in Flowcode
function. Confirmed real functions and their argument order:

- `Component.Property.SetValue(handle, propName, value)` — sets a
  property's stored value programmatically.
- `Component.Property.SetFilter(handle, propName, filterString)` —
  dynamically rewrites a `typeid='16'` dropdown's available choices, e.g.
  `"000PWM:0 Timer:0 Pin:A"` style encoded strings (only ever confirmed
  used on `typeid='16'` properties, never on `typeid='5'`).
- `Component.Property.SetVisible(handle, propOrFolderName, boolExpr)`
- `Component.Property.SetWritable(handle, propName, boolExpr)`
- `Component.Property.GetValue(handle, propName)` /
  `Component.Property.GetFilter(handle, propName)`
- `FCD.GetItemValue(path, key, default)` — reads target-device descriptor
  info, e.g. `FCD.GetItemValue("device.clock", "value", "20000000")` to
  read the selected chip's clock speed, or `FCD.GetItemValue("device", "cal", "")`
  to read its CAL/device-family string.
- `Component.GetParent(handle)` / `Component.GetChildHead(handle)` /
  `Component.GetNext(handle)` — walk the component tree.
- `Tree.GetValue(...)` / `Tree.GetSubValue(...)`, `FCD.GetPathHandle(...)`
- `Debug.PrintLn(...)`
- `this` — refers to the current component instance's own handle; used as
  the first argument to most `Component.Property.*` calls when a macro is
  acting on its own properties.

XML shape (confirmed, `argument`/`return` children in order):
```xml
<command class_type='sim' title='Simulation' macro='Component.Property.SetValue' >
  <argument exp='this' />
  <argument exp='&quot;PropertyName&quot;' />
  <argument exp='someValueOrExpr' />
</command>
```
A `sim` command that returns a value uses a `<return exp='.LocalVar' />`
child, same pattern as a component macro call:
```xml
<command class_type='sim' title='Simulation' macro='FCD.GetItemValue' >
  <return exp='.tempstr' />
  <argument exp='&quot;device.clock&quot;' />
  <argument exp='&quot;value&quot;' />
  <argument exp='&quot;20000000&quot;' />
</command>
```
An alternate inline call syntax also appears directly inside a
`calculation` command's `<exp>`, namespace-prefixed with `::` and spaces
around the dots: `::Component .Property .SetValue (this, "X", value)`.

### 9.3a `class_type='sim'` ALSO covers calling a CHILD COMPONENT's own
     macro ("Component Macro (Simulation Only)") — and THIS variant is
     unconditionally excluded from embedded compilation, no matter what
     calls it

Distinct from the built-in-function shape above (`macro='Component.Property.SetValue'`
with no `component=` attribute), confirmed real shape for flagging an
ordinary CHILD component macro call as simulation-only:

```xml
<command class_type='sim' title='Component Macro' component='LibraryComponent1' macro='FlashTx' />
```

This is the Flowcode UI's "Component Macro (Simulation Only)" command —
visually similar to an ordinary "Component Macro" call (`class_type='call'`,
Section 4), but a genuinely different command class. **Confirmed via a
real, working NEC_IR component (`LibraryComponent1::FlashTx`/`FlashRx`,
indicator flashes on a Library Component icon) that Flowcode strips
`class_type='sim'` commands from embedded C output UNCONDITIONALLY**,
regardless of whether the macro containing the call is reachable from a
real, embedded-compiled public API function. Placing
`<command class_type='sim' .../>` calling `FlashTx` directly inside the
real, publicly-reachable `SendByte`/`ProcessEdge` macros compiles and
links cleanly — no `api alt=` machinery (Section 13.7) needed, because
this exclusion happens per-command, not per-macro-reachability.

**This is easy to conflate with the Section 13.7 bug and doing so is a
real mistake this project made once** — do not assume every "simulation
indicator" or "simulation display" call needs the `api alt=` treatment.
The load-bearing question is always: *is the actual command a
`class_type='sim'` command, or an ordinary `class_type='call'`
Component Macro call?*
- `class_type='sim'` (whether the built-in-function shape in 9.3, or this
  child-component-macro shape) → automatically excluded from embedded
  output by Flowcode itself, safe to place directly in any real macro,
  no extra pattern needed.
- `class_type='call'` (an ordinary Component Macro / Call Macro call,
  e.g. to `GdiCanvas1::Clear`/`Update` in Section 13's drawing API) →
  compiled normally if reachable, and WILL cause a real link failure if
  the target component has no embedded implementation. This is what
  Section 13.7's `api alt=` mechanism actually exists to solve — it does
  NOT apply to `class_type='sim'` calls, which never needed it.
- Why the difference exists: `GdiCanvas`/`GdiText`/`GdiShape` are
  simulation-only 2D DRAWING components with no dedicated "flag this call
  as sim-only" UI option — every call to them (`Clear`, `Update`,
  `PlotPoint`, `SetText`, etc.) is an ordinary Component Macro call
  (`class_type='call'`), which is why they need the `api alt=` macro-
  swap pattern. A Library Component's simulation indicator macros
  (`FlashTx`/`FlashRx` etc.) are a different kind of thing Flowcode
  explicitly supports flagging per-call via `class_type='sim'` — check
  which command class an existing real macro actually used (the Interface
  Manager's "Simulation" macro-type option, mentioned in this document's
  intro, is the UI-side of the same idea) before assuming either pattern
  is needed; when unsure, the real, definitive test is a full compile-
  AND-link against real hardware (Section 7 / Section 13.7) — if it
  links clean, no fix is needed at all.

### 9.4 Other confirmed-real syntax pieces (from the same two reference
    files, not yet needed in this project's own components but real)

- **`goto` / `label`** command types exist for explicit flowchart
  goto/label control flow (`class_type='goto'`, `class_type='label'` with
  `labelid`/`labelname`/`labeltype` attributes).
- **String functions**: `Compare$`/`compare$`, `Length$`, `Right$`,
  `SplitString$`, `ToString$`, `StringToInt$`, and the `STRING <expr>`
  stringify-cast keyword.
- **Multi-dimensional / pointer string arrays** as local variables:
  `<local name='sa' type='T8*' ...><array size='200'/><array size='30'/></local>`
  — a `T8*` type with stacked `<array size='N'/>` children for each
  dimension. `T8` is Flowcode's string/text type.
- **`typeid='5'` (pin selection) properties never need an explicit
  `<variable>` declaration** — confirmed across three independent real
  files (this project's own `RxPin`, `HC_SR04`'s `OPP`/`ECHO` pins,
  `PWM.fcfx`'s `PORT`) — referenced directly by property name in
  expressions, same as any other property-backed value.

## 11. Single dynamic `typeid='16'` property pattern for multi-device pin choice
    (confirmed working on real Uno + Mega hardware, `PWM_HighRes_Timer1`)

Where a component needs to offer a different, device-dependent set of
choices for the SAME logical property (e.g. "which pin" when the pin
options differ between an ATmega328P and an ATmega2560), the confirmed
pattern is ONE `typeid='16'` property whose available options AND stored
value are both driven programmatically — not two separate properties
toggled with `Component.Property.SetVisible`, which was the initial
(unconfirmed, more complicated) approach this project tried first.

```xml
<property name='Output Pin' target='PwmPinSelect' typeid='16' hidden='0'
           locked='0' info='...' filter='000D9 (B1)&#10;001D10 (B2)' />
```

Inside the `Ev_Property_Change` (or `Ev_ChipChange`) macro, on detecting
the target device:

```xml
<command class_type='switch' title='Switch' exp='.DeviceIDLocal'>
  <case><flowline /></case>
  <case exp='0'>
    <flowline>
      <command class_type='sim' title='Simulation' macro='Component.Property.SetFilter'>
        <argument exp='this' />
        <argument exp='&quot;PwmPinSelect&quot;' />
        <argument exp='&quot;000D9 (B1)&#10;001D10 (B2)&quot;' />
      </command>
      <!-- clamp: if the previously-stored index is out of range for the
           new option list, reset it rather than leaving a stale/invalid
           selection -->
      <command class_type='calculation' title='Calculation'>
        <exp exp='.SelectedIndexLocal = PwmPinSelect' />
      </command>
      <command class_type='decision' title='Decision' exp='.SelectedIndexLocal &gt; 1' swap='0'>
        <flowline>
          <command class_type='sim' title='Simulation' macro='Component.Property.SetValue'>
            <argument exp='this' />
            <argument exp='&quot;PwmPinSelect&quot;' />
            <argument exp='&quot;000&quot;' />
          </command>
        </flowline>
        <flowline />
      </command>
    </flowline>
  </case>
  <case exp='1'>
    <flowline>
      <!-- same shape, with the Mega's 3-option filter string -->
    </flowline>
  </case>
</command>
```

Notes confirmed by actually building and hardware-testing this:

- `SetVisible` is not needed at all with this pattern — there is only ever
  one property, so nothing needs hiding/showing.
- The filter string's format is `NNNLabel` per option, joined with a
  newline (`\n` in the XML source, i.e. a literal newline character
  between options, not a literal backslash-n) — `NNN` is a zero-padded
  3-digit index matching what gets stored in the property's `<value>`.
- Filter option labels should be written for the actual end user, not for
  whoever is debugging the component. Register-name labels like `OC1A`
  meant nothing to this component's target audience (Arduino/Eblocks
  beginners); the confirmed-good convention that shipped is combining
  both notations beginners actually think in, e.g. `D9 (B1)` — the
  Arduino digital-pin number AND the AVR port-bit letter+number in one
  label, so it serves plain Arduino users and Flowcode Eblocks users at
  once.
- Always re-run `Ev_Property_Change` from `Ev_Initialise` (and from
  `Ev_ChipChange`) so the filter/value are correct immediately on load,
  not only after the user manually touches the property once — same
  reasoning as Section 9.0's "hidden auto-set property" note.

## 12. Multi-resolution public API instead of a single fixed-resolution
    property (design pattern, not Flowcode-schema-specific, but confirmed
    good practice from this project)

Rather than exposing one duty-cycle-style value as a fixed-resolution
property (which forces a resolution choice on every user regardless of
what precision they actually need, and which — per a real pre-Flowcode C
project's own documentation — misled users into thinking different pins
had different native resolutions when the difference was just old
application code, not hardware), the confirmed-good pattern is: no
property for the value at all, and instead multiple public API functions,
one per resolution the user might want to work in, e.g. `SetDutyCycle`
(0-100), `SetDutyCycleByte` (0-255), `SetDutyCycle10Bit` (0-1023),
`SetDutyCycle16Bit` (0-65535) — each one scaling its input up to a single
canonical highest-resolution internal value
(`.CanonicalValue = (input * MAXCANONICAL) / maxInputForThisFunction`)
stored in one component `<variable>`. This means:

- Whichever resolution function the user calls, results stay consistent
  (mixing calls, e.g. a rough `SetDutyCycle` followed later by a precise
  `SetDutyCycle16Bit`, just works, since both write into the same
  canonical variable via the same scaling logic).
- The Properties panel stays uncluttered by a value that's naturally a
  runtime/firmware concern, not a design-time one.
- `Enable()`/`Disable()` should be implemented via one boolean/flag
  `<variable>` (e.g. `OutputEnabled`) rather than a separate "saved last
  duty" variable — the apply-to-hardware macro always reads the flag and
  either applies the canonical value or forces 0, so `Disable()` never
  loses/needs to separately remember the last duty; `Enable()` just flips
  the flag back and the untouched canonical value takes effect again.

## 13. The 2D simulation-drawing API — `GdiCanvas` / `GdiText` / `GdiShape`
    child components (confirmed real syntax, extracted from Matrix's own
    official `PWM_Output.fcfx` "PWM (Internal)" component, guid
    `444fb704-814c-4707-a15c-759ba088505c`, author='Matrix Ltd')

This is the mechanism for drawing a custom on-icon simulation display (an
oscilloscope-style trace, a live readout, an LED indicator, etc) — i.e.
graphics rendered directly on the component's own box in the 2D panel
during simulation, as opposed to the panel/pin/property mechanisms covered
elsewhere in this document.

**Correction (see Section 13.7 — confirmed via a real link error, not
guessed): calls to these components are NOT automatically excluded from
the embedded build the way Section 9's `sim`-class commands are.** An
earlier draft of this section wrongly assumed they were "simulation-only
in the same sense" as `sim`-class commands, with no footprint in
generated embedded C. That is false: a `GdiCanvas`/`GdiText`/`GdiShape`
macro call is an ORDINARY macro call (no special `class_type`), and if
it's reachable from a real, embedded-compiled macro, Flowcode compiles a
real call to it — which then fails at the LINK step, since these
components have no real hardware implementation to link against. Keeping
drawing-component calls out of the embedded build requires the `api alt=`
mechanism in Section 13.7, not an automatic exclusion.

### 13.1 The three drawing child component types

Declared as ordinary child `<component>` entries (siblings of any other
child, e.g. before the `LibraryComponent1` wrapper), each `visible='0'`
except where the component itself is meant to be seen on the icon
(confirmed: the reference's `LED_Indicator` is `visible='1'`; its
`GdiCanvas`/`GdiText` children are all `visible='0'` yet still render into
the simulation view — `visible` here governs something else, not whether
simulation drawing appears).

- **`class_type='GdiCanvas'`** — a pixel-drawable canvas.
  Key `<values>`: `nWidth`, `nHeight` (pixel dimensions of the drawing
  surface), `nStyle`, `bLockAspect`, `colBackground`, `colForeground`
  (24-bit decimal colour values).
  ```xml
  <component class_type='GdiCanvas' codename='GdiCanvas1' ... visible='0' ...>
    <values>
      <value target='nWidth' data='220' />
      <value target='nHeight' data='100' />
      <value target='nStyle' data='2' />
      <value target='bLockAspect' data='0' />
      <value target='colBackground' data='3552822' />
      <value target='colForeground' data='65280' />
    </values>
  </component>
  ```
  Controlling macros, called as component-macro calls from any flowchart
  macro (`class_type='call'` for the no-arg ones, `class_type='sim'` when
  arguments are needed — both forms are confirmed to work):
  - `Clear` (no args) — resets the canvas to its background colour.
  - `Update` (no args) — flushes/renders the canvas's current pixel state
    to screen. Call this AFTER a batch of `PlotPoint` calls, not after
    each one, for a static (non-flickering) redraw-on-change design.
  - `PlotPoint(x, y, colorHex)` — 3 arguments: integer pixel coordinates
    and a 24-bit hex colour literal (e.g. `0xFFFFFF` white, `0x5757FF`
    blue, `0xFF0000` red). One call plots one pixel; a line/shape is drawn
    by looping this over the coordinates you want lit.
    ```xml
    <command class_type='sim' title='Component Macro' component='GdiCanvas1' macro='PlotPoint'>
      <argument exp='.X' />
      <argument exp='.Y' />
      <argument exp='0x5757FF' />
    </command>
    ```

- **`class_type='GdiText'`** — a styled text label. Key `<values>`:
  `sText` (initial text), `fntFamily`, `iFontSize`, `bBold`/`bItalic`/
  `bUnderline`, `colTextColour`/`colTextGradient` (decimal colour),
  `nHorizontalAlignment`/`nVerticalAlignment`, `dScale`,
  `colBackgroundColour`/`colBackgroundGradient` (`-1` = transparent).
  Controlled with a dedicated `SetText` macro taking one string argument:
  ```xml
  <command class_type='sim' title='Component Macro' component='GdiText1' macro='SetText'>
    <argument exp='.Str' />
  </command>
  ```

- **`class_type='GdiShape'`** — a filled/outlined shape (used by the
  reference for a circular LED indicator: `nType='  1'` with
  `iRounding='25'` gives a filled circle). Key `<values>`: `colFill`,
  `colFillGradient`, `nGradientStyle`, `nFillOpacity`, `colOutline`,
  `colOutlineGradient`, `iOutlineSize`. **There is no dedicated
  "SetColor"-style macro** — colour is changed by writing straight to the
  property via the already-known `Component.Property.SetValue` built-in
  (Section 9.3), targeting the shape's own codename:
  ```xml
  <command class_type='sim' title='Simulation' macro='Component.Property.SetValue'>
    <argument exp='LED_Indicator' />
    <argument exp='&quot;colFill&quot;' />
    <argument exp='0x80FF57' />
  </command>
  ```
  Confirmed real ON/OFF colour pairs for a status LED, from the
  reference's own `EnableSim`/`DisableSim` macros:
  - **OFF**: `colFill = 0x3C3C3C` (dark grey), `colFillGradient =
    0x007000` (dark green) — gives a dim, "not lit" look.
  - **ON**: `colFill = 0x80FF57` (light green), `colFillGradient =
    0xFFFFFF` (white) — gives a bright, glossy "lit" look.

### 13.2 Confirmed pixel-plotting technique for a mark:space waveform trace

Extracted in full from the reference's `SimDrawDigitalWaveform` macro
(the pattern this project's own `SimDrawWaveform` macro in
`PWM_HighRes_Timer1` was adapted from). Given a duty value expressed as a
0-100 float (call it `.DutyPercent`), on a canvas at least ~112px wide:

1. `Clear` the canvas.
2. Draw a baseline row of white tick pixels at a fixed `y` (e.g. `y=60`)
   for `x = 0..9` — a small leading reference mark before the trace
   itself starts at `x=10`.
3. If `.DutyPercent` is nonzero:
   - Loop `y` from the baseline up by 30px, plotting a blue vertical line
     at `x=10` (the mark's rising edge) each iteration; if
     `.DutyPercent <= 99`, also plot a red vertical line at
     `x = .DutyPercent + 10` (the mark's falling edge / space start) and a
     second blue vertical line at a fixed `x=110` (next mark's rising
     edge) — skipped entirely when duty is essentially saturated (>99%).
   - Loop `x` from 0 to `.DutyPercent` (inclusive), plotting a blue pixel
     at `y=30` (the "mark" horizontal bar) and a parallel white pixel at
     `y=25` (a duty-ratio indicator line) at each `x + 10`.
   - Loop a short 5px vertical tick at both `x=10` and
     `x = .DutyPercent + 10`, at `y = 27 - count` — these are the bracket
     ends of the indicator line, visually marking where the mark portion
     starts and ends.
   - Loop the remaining width, plotting red pixels at `y=60` from
     `x = .DutyPercent + 10` out to the canvas's right edge — the "space"
     portion of the baseline.
4. If `.DutyPercent` is exactly 0, instead draw a single all-red baseline
   row across the full width — representing constant-low output, with no
   mark portion to show at all.
5. `Update` the canvas to render everything plotted since the last
   `Clear`.

**Important correction, confirmed the hard way against a real running
component**: the reference's own macro plots `.DutyPercent` (0-100)
directly as an X pixel offset, and uses fixed edge constants (`110` for
the next mark's rising edge, `102 - .DutyPercent` for the remaining
space-fill width, `112` for the full-width duty-0% line) that assume the
trace should occupy roughly a 112px-wide strip. If the trace needs to be
narrower or wider than that (e.g. to make better use of a wider
`GdiCanvas` — this project's own canvas is `nWidth=220`, more than double
that 112px strip), **resizing the `GdiCanvas` child component's own
`xsz`/`ysz` (or a `class_type='group'` wrapper around it, Section 13.6)
does NOT change where the trace draws** — it only stretches/distorts the
already-plotted bitmap, since the pixel coordinates themselves are
computed independently of the canvas's on-screen size. The actual fix
must touch the drawing macro's own math:

- Introduce a separate scaled local (e.g. `.DutyPx`), computed as
  `.DutyPx = .DutyPercent * SCALE` (where `SCALE` is the desired period
  width in pixels divided by 100 — e.g. `SCALE = 1.8` for a ~180px-wide
  period), and use `.DutyPx` everywhere `.DutyPercent` was used as an X
  COORDINATE. Keep using `.DutyPercent` (unscaled) anywhere it's actually
  a percentage — the duty-vs-99%-saturation check, and the "Duty = X%"
  text label — since those aren't pixel positions.
- Recompute the fixed edge constants to match: the "next mark" X position
  becomes `10 + (100 * SCALE)`, the full-width duty-0% loop bound becomes
  the same value, and the remaining-space-fill loop bound becomes
  `(100 * SCALE) - .DutyPx`.
- Confirmed on `PWM_HighRes_Timer1`: `SCALE = 1.8` (period width ~180px,
  next-mark edge at `x=190`) filled a `nWidth=220` canvas nicely at
  reasonable duty/frequency combinations, including an extreme real test
  case (250kHz, 15% duty, sub-microsecond mark time) which rendered
  correctly once the math itself — not just the box — was rescaled.

This produces a static (non-animating) picture that only needs redrawing
when duty/frequency/enable state actually changes — call the drawing
macro from wherever those values get applied (e.g. at the end of an
"apply to hardware" macro), not on a continuous timer, if a live scope
trace is NOT what's wanted (confirmed as the deliberate, simpler design
choice for `PWM_HighRes_Timer1`, as opposed to the debounced-timer
redraw pattern in 13.3 below, which the reference component uses instead
for a live/animated feel).

### 13.3 Confirmed-real but NOT adopted: debounced-timer redraw

The reference component redraws ~200ms after a property change rather
than instantly, via `System.TimerStart(timerId, delayMs)` firing an
`Ev_Timer(TimerID)` lifecycle event (see Section 9.1's event list), guarded
by a boolean flag so only one pending timer ever exists at once. This is
real, working syntax, but was deliberately NOT used in
`PWM_HighRes_Timer1` in favour of the simpler direct-call, redraw-on-change
approach in 13.2 — recorded here in case a future component genuinely
wants the live/debounced feel.

### 13.4 Two distinct `SetVisible` calls — do not confuse them

- `Component.Property.SetVisible(this, propOrFolderName, boolExpr)`
  (already documented in Section 9.3) toggles whether a PROPERTY (or a
  folder of properties) is shown in the Properties panel.
- **`Component.SetVisible(childCodename, boolExpr)`** — a DIFFERENT,
  separately-confirmed built-in — toggles whether an entire CHILD
  COMPONENT is shown/rendered at all (used by the reference to switch
  between two alternate simulation displays — a digital waveform vs. an
  analogue needle gauge — based on a mode property).

### 13.5 Other confirmed-real built-ins from the same reference file

- **`Panel.Position.MoveTo(componentCodename, x, y, z)`** — repositions a
  child component on the 2D panel at runtime.
- **`Ev_Start` / `Ev_Stop` / `Ev_Pause` simulation lifecycle events**
  (`class='Simulation' event='Start'/'Stop'/'Pause'`, extending the event
  list in Section 9.1) — fire when the user starts/stops/pauses a
  simulation run in the IDE. Confirmed use: forcing an initial
  "disabled-look" draw at `Ev_Start` (so the display doesn't show stale
  data from a previous run before the user's own code runs), and forcing
  the enabled-state flag off (and, for a status LED, forcing its colour to
  the OFF pair from 13.1) at `Ev_Stop`, independent of whatever the
  component's real enable/disable state was when the simulation stopped —
  i.e. "simulation stopped" should visually override "output was left
  enabled," since the chip isn't actually running anymore.

### 13.6 Grouping several 2D drawing children to move/resize them as one unit
    (confirmed via a real file the user edited directly in Flowcode's own
    2D panel editor, not guessed)

When a simulation display is built from several separate children (a
`GdiCanvas`, multiple `GdiText` labels, a `GdiShape` LED), repositioning or
resizing the whole assembly by hand-editing each child's `x`/`y`/`xsz`/`ysz`
independently (which an earlier draft of this document's own example did)
is fragile and easy to get visually wrong without live feedback. The
confirmed-real, much better approach: select all the drawing children in
Flowcode's own 2D panel view and group them (`class_type='group'`). This
introduces a new wrapper component:

```xml
<component class_type='group' codename='group1' panelId='0' x='359.5'
            y='-197.015' z='0' xsz='1.66286' ysz='1.66286' zsz='1' ...>
  <resources /><properties /><values /><events /><apis /><variables />
  <macros />
  <component class_type='GdiCanvas' codename='GdiCanvas1' ...>...</component>
  <component class_type='GdiText' codename='GdiText1' ...>...</component>
  <!-- etc: all the drawing children now live INSIDE the group, each
       keeping their own class_type/codename/macros unchanged -->
</component>
```

Confirmed behaviour:
- The children's `x`/`y` coordinates become relative to the group's own
  local origin, not the overall icon's origin.
- The GROUP's own `xsz`/`ysz` act as a uniform (or non-uniform, if set
  independently) SCALE FACTOR applied to the whole grouped assembly —
  e.g. `xsz='1.66286' ysz='1.66286'` scales everything inside up by about
  66%, keeping every child's relative layout intact. This means resizing
  the whole display later is a single drag on the group's own bounding
  box in the editor (or a single two-number edit), not re-deriving every
  child's coordinates by hand.
- Grouping does NOT change any child's `class_type`, `codename`, or the
  macro calls that target it by codename (`component='GdiCanvas1'` etc
  still work unchanged) — only its position/size becomes group-relative.
- **This is the right tool reached for by resizing/repositioning a
  multi-element simulation display, in preference to computing scaled
  coordinates by hand** — the latter was tried once in this project and
  produced a plausible-looking but unverified guess; the real, working
  fix the user actually applied was to group the elements in the editor
  and resize the group directly, which is also just easier to get right
  since it gives live visual feedback.

### 13.7 CRITICAL: a simulation-drawing macro called from a real, embedded-
    reachable macro WILL be linked into the embedded build and fail — the
    `api alt=` mechanism is the real, confirmed fix

This is the single most important correction in this whole section, found
via a REAL `avr-gcc`/`ld` failure from the user's own build (not a
compile error — a LINK error), after `PWM_HighRes_Timer1`'s `ApplyPWM`
macro (real, embedded-reachable — called from every public `SetDutyCycle*`/
`SetFrequency`/`Enable`/`Disable` macro) itself called `SimDrawWaveform`,
which in turn called `GdiCanvas1::Clear`/`Update`:

```
undefined reference to `FCD_0c081_GdiCanvas1__Clear'
undefined reference to `FCD_0c081_GdiCanvas1__Update'
```

**This disproves an earlier, unverified assumption in this document** —
that calls to simulation-only 2D drawing components (`GdiCanvas`/
`GdiText`/`GdiShape`) would simply compile to harmless no-op stubs on a
real embedded target. They do not. If a macro that touches one of these
components is reachable from any macro that is itself reachable from a
real public API function, Flowcode happily compiles a real call to it
into the embedded `.c` file — and since `GdiCanvas1`/etc have no real
hardware implementation to link against, the build fails at the LINK
step, not earlier. A compile that succeeds is not proof a component's
simulation code is safe to ship; only a full compile-AND-LINK against the
real target proves it (this project's established `avr-gcc` sanity-check
habit — Section 7 — needs to include the link step, not just parsing/
compiling, to catch this class of bug).

**The real, confirmed fix — extracted directly from Matrix's own
`PWM_Output.fcfx`, not guessed**: every public API macro that a
simulation display needs to react to gets a SEPARATE, parallel macro with
an IDENTICAL parameter list, wired via the `alt` attribute on that
macro's `<api>` entry:

```xml
<apis>
  <api name='SetDutyCycle' alt='SetDutyCycleSim' type='1' proto='1' />
  <api name='Enable' alt='EnableSim' type='1' proto='1' />
  <!-- one alt= pair per public function the display needs to react to -->
</apis>
```

Confirmed behaviour of this mechanism:
- The REAL macro (`SetDutyCycle`) is what actually gets compiled into
  embedded firmware, and must contain ZERO references to any
  `GdiCanvas`/`GdiText`/`GdiShape` component, direct or indirect (no
  calling a macro that calls one, transitively) — it should do only real
  work (update the component's own state variables, call the macro that
  contains the native hardware-register code).
- The ALT macro (`SetDutyCycleSim`) is what Flowcode's SIMULATOR actually
  runs instead, when the component is exercised inside Flowcode's own
  simulation engine (e.g. a user's test project calling `SetDutyCycle(20)`
  while simulating, not exporting for real hardware) — confirmed the real
  macro's logic (including any native-ccode-containing macro it calls)
  does NOT also run in this case; the alt macro is a full, independent
  replacement, not a supplement.
- **The alt macro's parameter list must match the real macro's exactly**
  (same param names, types, order) — confirmed both by the reference file
  (every `Sim`-suffixed macro mirrors its real counterpart's single
  parameter one-for-one) and by direct instruction from the person running
  this project, who has done this before.
- Because the alt macro is NEVER called from the real macro (they are two
  independent implementations Flowcode chooses between), it can safely
  call a simulation-drawing macro (`SimDrawWaveform`, or the reference's
  `SimDrawDigitalWaveform`) directly — this can NEVER end up compiled into
  the embedded build, since nothing embedded-reachable ever calls an alt
  macro.
- **Practical pattern for a component whose real logic already stores its
  state in ordinary flowchart `<variable>`s** (as `PWM_HighRes_Timer1`
  already did — `CurrentDuty16`, `CurrentFrequency`, `OutputEnabled`): the
  alt macro can simply repeat the same variable-update line(s) from the
  real macro, then call the drawing macro directly — no separate
  `SimDuty`-style shadow variable is needed unless the real macro's state
  lives somewhere the alt macro can't reach (e.g. inside a native-ccode-
  only local, per Section 7 — in that case, mirror the reference's
  approach of a dedicated `Sim`-prefixed global the alt macros write and
  the drawing macro reads).
- An entirely different, ALSO-confirmed-real alternative the reference
  demonstrates (not needed for a simple redraw-on-change design, but
  available for a debounced/live-feel display): have the alt macros kick
  off `System.TimerStart` (Section 13.3) instead of calling the drawing
  macro directly, and do the actual drawing from `Ev_Timer` — since
  `System.TimerStart` is itself a `sim`-class command (Section 9.3, never
  compiled into firmware) and `Ev_Timer` is a lifecycle event macro
  (Section 9.0, design-time/simulation-engine only), this achieves the
  same "never reaches the embedded build" guarantee through a different
  route, at the cost of a small delay and needing a running-flag to avoid
  stacking multiple pending timers.
- **Lifecycle event macros (`Ev_Property_Change`, `Ev_Initialise`,
  `Ev_SimStart`, `Ev_SimStop` etc, per Section 9.0/9.1) calling a
  simulation-drawing macro directly is fine and does NOT need this alt=
  treatment** — they are design-time/simulation-engine-only by nature, so
  a direct call from one of them was not the cause of this bug. The bug
  was specifically a REAL macro (`ApplyPWM`, reachable from real public
  API functions) calling the drawing macro — any macro reachable that way
  is the thing to check for accidental simulation-only component calls.
- **Do NOT reach for this pattern for a `class_type='sim'` "Component
  Macro (Simulation Only)" call (e.g. a Library Component's `FlashTx`/
  `FlashRx` indicator macro) — see Section 9.3a.** That command class is
  excluded from embedded output unconditionally by Flowcode itself, no
  matter what real macro it's placed in, so it needs no `api alt=`
  swap-macro at all. This project built an unnecessary `TransmitNECSim`/
  `ProcessEdgeSim`/`ProcessEdgeCore` split for exactly this reason before
  catching the mistake — the giveaway was that the calls in question were
  `class_type='sim'`, not `class_type='call'` like the `GdiCanvas` case
  that actually motivated this section. Reach for `api alt=` only when
  the simulation-only component has no per-call "simulation only" flag
  and is instead called via an ordinary Component Macro (`class_type=
  'call'`) — `GdiCanvas`/`GdiText`/`GdiShape` are the confirmed example.

## 14. What this document deliberately does NOT cover

Anything specific to the NEC IR protocol itself, the `NEC_IR` component's
own state machine, or the design decisions behind THAT component (why
`IsHeld()` is a macro not a property, the `EdgeTimeoutTicks` mechanism,
etc.) lives in `NEC_IR_Full_Handover_3.md`, not here. This document is
meant to be useful for building or editing ANY Flowcode component, not
just that one.
