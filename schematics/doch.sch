<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.6.2">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="CanCubeSat">
<packages>
<package name="LQFP48">
<description>&lt;b&gt;LQFP48&lt;/b&gt;&lt;p&gt;
7 x 7 mm, 48-pin low-profile quad flat package</description>
<wire x1="-3.5" y1="-3.5" x2="-3.5" y2="-3.29" width="0.127" layer="21"/>
<wire x1="-3.5" y1="-3.28" x2="-3.5" y2="3.5" width="0.127" layer="21"/>
<wire x1="-3.5" y1="3.5" x2="3.5" y2="3.5" width="0.127" layer="21"/>
<wire x1="3.5" y1="3.5" x2="3.5" y2="-3.5" width="0.127" layer="21"/>
<wire x1="3.5" y1="-3.5" x2="-3.5" y2="-3.5" width="0.127" layer="21"/>
<circle x="-2.93" y="-2.94" radius="0.306103125" width="0.127" layer="21"/>
<text x="-2.84" y="1.35" size="1.27" layer="25">&gt;Name</text>
<text x="-2.84" y="-1.85" size="1.27" layer="27">&gt;Value</text>
<rectangle x1="-2.86" y1="-4.5" x2="-2.64" y2="-3.5" layer="51"/>
<rectangle x1="-2.36" y1="-4.5" x2="-2.14" y2="-3.5" layer="51"/>
<rectangle x1="-1.86" y1="-4.5" x2="-1.64" y2="-3.5" layer="51"/>
<rectangle x1="-1.36" y1="-4.5" x2="-1.14" y2="-3.5" layer="51"/>
<rectangle x1="-0.86" y1="-4.5" x2="-0.64" y2="-3.5" layer="51"/>
<rectangle x1="-0.36" y1="-4.5" x2="-0.14" y2="-3.5" layer="51"/>
<rectangle x1="0.14" y1="-4.5" x2="0.36" y2="-3.5" layer="51"/>
<rectangle x1="0.64" y1="-4.5" x2="0.86" y2="-3.5" layer="51"/>
<rectangle x1="1.14" y1="-4.5" x2="1.36" y2="-3.5" layer="51"/>
<rectangle x1="1.64" y1="-4.5" x2="1.86" y2="-3.5" layer="51"/>
<rectangle x1="2.14" y1="-4.5" x2="2.36" y2="-3.5" layer="51"/>
<rectangle x1="2.64" y1="-4.5" x2="2.86" y2="-3.5" layer="51"/>
<rectangle x1="3.89" y1="-3.25" x2="4.11" y2="-2.25" layer="51" rot="R90"/>
<rectangle x1="3.89" y1="-2.75" x2="4.11" y2="-1.75" layer="51" rot="R90"/>
<rectangle x1="3.89" y1="-2.25" x2="4.11" y2="-1.25" layer="51" rot="R90"/>
<rectangle x1="3.89" y1="-1.75" x2="4.11" y2="-0.75" layer="51" rot="R90"/>
<rectangle x1="3.89" y1="-1.25" x2="4.11" y2="-0.25" layer="51" rot="R90"/>
<rectangle x1="3.89" y1="-0.75" x2="4.11" y2="0.25" layer="51" rot="R90"/>
<rectangle x1="3.89" y1="-0.25" x2="4.11" y2="0.75" layer="51" rot="R90"/>
<rectangle x1="3.89" y1="0.25" x2="4.11" y2="1.25" layer="51" rot="R90"/>
<rectangle x1="3.89" y1="0.75" x2="4.11" y2="1.75" layer="51" rot="R90"/>
<rectangle x1="3.89" y1="1.25" x2="4.11" y2="2.25" layer="51" rot="R90"/>
<rectangle x1="3.89" y1="1.75" x2="4.11" y2="2.75" layer="51" rot="R90"/>
<rectangle x1="3.89" y1="2.25" x2="4.11" y2="3.25" layer="51" rot="R90"/>
<rectangle x1="2.64" y1="3.5" x2="2.86" y2="4.5" layer="51" rot="R180"/>
<rectangle x1="2.14" y1="3.5" x2="2.36" y2="4.5" layer="51" rot="R180"/>
<rectangle x1="1.64" y1="3.5" x2="1.86" y2="4.5" layer="51" rot="R180"/>
<rectangle x1="1.14" y1="3.5" x2="1.36" y2="4.5" layer="51" rot="R180"/>
<rectangle x1="0.64" y1="3.5" x2="0.86" y2="4.5" layer="51" rot="R180"/>
<rectangle x1="0.14" y1="3.5" x2="0.36" y2="4.5" layer="51" rot="R180"/>
<rectangle x1="-0.36" y1="3.5" x2="-0.14" y2="4.5" layer="51" rot="R180"/>
<rectangle x1="-0.86" y1="3.5" x2="-0.64" y2="4.5" layer="51" rot="R180"/>
<rectangle x1="-1.36" y1="3.5" x2="-1.14" y2="4.5" layer="51" rot="R180"/>
<rectangle x1="-1.86" y1="3.5" x2="-1.64" y2="4.5" layer="51" rot="R180"/>
<rectangle x1="-2.36" y1="3.5" x2="-2.14" y2="4.5" layer="51" rot="R180"/>
<rectangle x1="-2.86" y1="3.5" x2="-2.64" y2="4.5" layer="51" rot="R180"/>
<rectangle x1="-4.11" y1="2.25" x2="-3.89" y2="3.25" layer="51" rot="R270"/>
<rectangle x1="-4.11" y1="1.75" x2="-3.89" y2="2.75" layer="51" rot="R270"/>
<rectangle x1="-4.11" y1="1.25" x2="-3.89" y2="2.25" layer="51" rot="R270"/>
<rectangle x1="-4.11" y1="0.75" x2="-3.89" y2="1.75" layer="51" rot="R270"/>
<rectangle x1="-4.11" y1="0.25" x2="-3.89" y2="1.25" layer="51" rot="R270"/>
<rectangle x1="-4.11" y1="-0.25" x2="-3.89" y2="0.75" layer="51" rot="R270"/>
<rectangle x1="-4.11" y1="-0.75" x2="-3.89" y2="0.25" layer="51" rot="R270"/>
<rectangle x1="-4.11" y1="-1.25" x2="-3.89" y2="-0.25" layer="51" rot="R270"/>
<rectangle x1="-4.11" y1="-1.75" x2="-3.89" y2="-0.75" layer="51" rot="R270"/>
<rectangle x1="-4.11" y1="-2.25" x2="-3.89" y2="-1.25" layer="51" rot="R270"/>
<rectangle x1="-4.11" y1="-2.75" x2="-3.89" y2="-1.75" layer="51" rot="R270"/>
<rectangle x1="-4.11" y1="-3.25" x2="-3.89" y2="-2.25" layer="51" rot="R270"/>
<smd name="1" x="-2.75" y="-4.25" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="2" x="-2.25" y="-4.25" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="3" x="-1.75" y="-4.25" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="4" x="-1.25" y="-4.25" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="5" x="-0.75" y="-4.25" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="6" x="-0.25" y="-4.25" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="7" x="0.25" y="-4.25" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="8" x="0.75" y="-4.25" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="9" x="1.25" y="-4.25" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="10" x="1.75" y="-4.25" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="11" x="2.25" y="-4.25" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="12" x="2.75" y="-4.25" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="13" x="4.25" y="-2.75" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="14" x="4.25" y="-2.25" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="15" x="4.25" y="-1.75" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="16" x="4.25" y="-1.25" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="17" x="4.25" y="-0.75" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="18" x="4.25" y="-0.25" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="19" x="4.25" y="0.25" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="20" x="4.25" y="0.75" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="21" x="4.25" y="1.25" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="22" x="4.25" y="1.75" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="23" x="4.25" y="2.25" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="24" x="4.25" y="2.75" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="25" x="2.75" y="4.25" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="26" x="2.25" y="4.25" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="27" x="1.75" y="4.25" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="28" x="1.25" y="4.25" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="29" x="0.75" y="4.25" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="30" x="0.25" y="4.25" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="31" x="-0.25" y="4.25" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="32" x="-0.75" y="4.25" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="33" x="-1.25" y="4.25" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="34" x="-1.75" y="4.25" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="35" x="-2.25" y="4.25" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="36" x="-2.75" y="4.25" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="37" x="-4.25" y="2.75" dx="1.2" dy="0.3" layer="1"/>
<smd name="38" x="-4.25" y="2.25" dx="1.2" dy="0.3" layer="1"/>
<smd name="39" x="-4.25" y="1.75" dx="1.2" dy="0.3" layer="1"/>
<smd name="40" x="-4.25" y="1.25" dx="1.2" dy="0.3" layer="1"/>
<smd name="41" x="-4.25" y="0.75" dx="1.2" dy="0.3" layer="1"/>
<smd name="42" x="-4.25" y="0.25" dx="1.2" dy="0.3" layer="1"/>
<smd name="43" x="-4.25" y="-0.25" dx="1.2" dy="0.3" layer="1"/>
<smd name="44" x="-4.25" y="-0.75" dx="1.2" dy="0.3" layer="1"/>
<smd name="45" x="-4.25" y="-1.25" dx="1.2" dy="0.3" layer="1"/>
<smd name="46" x="-4.25" y="-1.75" dx="1.2" dy="0.3" layer="1"/>
<smd name="47" x="-4.25" y="-2.25" dx="1.2" dy="0.3" layer="1"/>
<smd name="48" x="-4.25" y="-2.75" dx="1.2" dy="0.3" layer="1"/>
</package>
<package name="LGA-14">
<wire x1="-1.5" y1="1.25" x2="-1.5" y2="-1.25" width="0.127" layer="21"/>
<wire x1="-1.5" y1="-1.25" x2="1.5" y2="-1.25" width="0.127" layer="21"/>
<wire x1="1.5" y1="-1.25" x2="1.5" y2="1.25" width="0.127" layer="21"/>
<wire x1="1.5" y1="1.25" x2="-1.5" y2="1.25" width="0.127" layer="21"/>
<smd name="P$11" x="1.225" y="0.775" dx="0.8" dy="0.4" layer="1"/>
<smd name="P$10" x="1.2" y="0.25" dx="0.8" dy="0.35" layer="1"/>
<smd name="P$9" x="1.2" y="-0.25" dx="0.8" dy="0.35" layer="1"/>
<smd name="P$8" x="1.225" y="-0.775" dx="0.8" dy="0.4" layer="1"/>
<smd name="P$7" x="0.5" y="-0.95" dx="0.8" dy="0.35" layer="1" rot="R90"/>
<smd name="P$6" x="0" y="-0.95" dx="0.8" dy="0.35" layer="1" rot="R90"/>
<smd name="P$5" x="-0.5" y="-0.95" dx="0.8" dy="0.35" layer="1" rot="R90"/>
<smd name="P$4" x="-1.225" y="-0.775" dx="0.8" dy="0.4" layer="1" rot="R180"/>
<smd name="P$3" x="-1.2" y="-0.25" dx="0.8" dy="0.35" layer="1" rot="R180"/>
<smd name="P$2" x="-1.2" y="0.25" dx="0.8" dy="0.35" layer="1" rot="R180"/>
<smd name="P$1" x="-1.225" y="0.775" dx="0.8" dy="0.4" layer="1" rot="R180"/>
<smd name="P$14" x="-0.5" y="0.95" dx="0.8" dy="0.35" layer="1" rot="R270"/>
<smd name="P$13" x="0" y="0.95" dx="0.8" dy="0.35" layer="1" rot="R270"/>
<smd name="P$12" x="0.5" y="0.95" dx="0.8" dy="0.35" layer="1" rot="R270"/>
<text x="-1.5" y="1.5" size="0.6096" layer="25">&gt;NAME</text>
</package>
<package name="BME280C">
<wire x1="-1.25" y1="1.25" x2="-1.25" y2="-1.25" width="0.127" layer="21"/>
<wire x1="-1.25" y1="-1.25" x2="1.25" y2="-1.25" width="0.127" layer="21"/>
<wire x1="1.25" y1="-1.25" x2="1.25" y2="1.25" width="0.127" layer="21"/>
<wire x1="1.25" y1="1.25" x2="-1.25" y2="1.25" width="0.127" layer="21"/>
<smd name="1" x="1.025" y="0.975" dx="0.5" dy="0.35" layer="1"/>
<smd name="2" x="1.025" y="0.325" dx="0.5" dy="0.35" layer="1"/>
<smd name="3" x="1.025" y="-0.325" dx="0.5" dy="0.35" layer="1"/>
<smd name="4" x="1.025" y="-0.975" dx="0.5" dy="0.35" layer="1"/>
<smd name="5" x="-1.025" y="-0.975" dx="0.5" dy="0.35" layer="1"/>
<smd name="6" x="-1.025" y="-0.325" dx="0.5" dy="0.35" layer="1"/>
<smd name="8" x="-1.025" y="0.975" dx="0.5" dy="0.35" layer="1"/>
<smd name="7" x="-1.025" y="0.325" dx="0.5" dy="0.35" layer="1"/>
<text x="-1.2" y="1.5" size="0.5" layer="25" font="vector">&gt;NAME</text>
</package>
<package name="GOOUUUATGM336H">
<wire x1="-5.05" y1="4.85" x2="-5.05" y2="-4.85" width="0.127" layer="21"/>
<wire x1="-5.05" y1="-4.85" x2="5.05" y2="-4.85" width="0.127" layer="21"/>
<wire x1="5.05" y1="-4.85" x2="5.05" y2="4.85" width="0.127" layer="21"/>
<wire x1="5.05" y1="4.85" x2="-5.05" y2="4.85" width="0.127" layer="21"/>
<pad name="1" x="4" y="4" drill="0.6" shape="square"/>
<pad name="2" x="4" y="2" drill="0.6"/>
<pad name="3" x="4" y="0" drill="0.6"/>
<pad name="4" x="4" y="-2" drill="0.6"/>
<pad name="5" x="4" y="-4" drill="0.6"/>
<wire x1="-4" y1="4" x2="-4" y2="-4" width="0.127" layer="21"/>
<wire x1="-4" y1="-4" x2="2" y2="-4" width="0.127" layer="21"/>
<wire x1="2" y1="-4" x2="2" y2="4" width="0.127" layer="21"/>
<wire x1="2" y1="4" x2="-4" y2="4" width="0.127" layer="21"/>
<text x="-3" y="5" size="1.27" layer="25" font="vector">&gt;NAME</text>
</package>
</packages>
<symbols>
<symbol name="STM32_48PIN_TYP3">
<pin name="PA0-WKUP" x="22.86" y="-40.64" length="middle" rot="R180"/>
<pin name="PA1" x="22.86" y="-38.1" length="middle" rot="R180"/>
<pin name="PA2" x="22.86" y="-35.56" length="middle" rot="R180"/>
<pin name="PA3" x="22.86" y="-33.02" length="middle" rot="R180"/>
<pin name="PA4" x="22.86" y="-30.48" length="middle" rot="R180"/>
<pin name="PA5" x="22.86" y="-27.94" length="middle" rot="R180"/>
<pin name="PA6" x="22.86" y="-25.4" length="middle" rot="R180"/>
<pin name="PA7" x="22.86" y="-22.86" length="middle" rot="R180"/>
<pin name="PA9" x="22.86" y="-17.78" length="middle" rot="R180"/>
<pin name="PA10" x="22.86" y="-15.24" length="middle" rot="R180"/>
<pin name="PA13" x="22.86" y="-7.62" length="middle" rot="R180"/>
<pin name="PA14" x="22.86" y="-5.08" length="middle" rot="R180"/>
<pin name="PB0" x="22.86" y="2.54" length="middle" rot="R180"/>
<pin name="VDDA" x="-22.86" y="-30.48" length="middle" direction="pwr"/>
<pin name="BOOT0" x="-22.86" y="-40.64" length="middle" direction="in"/>
<pin name="NRST" x="-22.86" y="-38.1" length="middle" function="dot"/>
<pin name="OSC_IN" x="-22.86" y="-15.24" length="middle" function="clk"/>
<pin name="OSC_OUT" x="-22.86" y="-20.32" length="middle" function="clk"/>
<wire x1="-17.78" y1="-43.18" x2="-17.78" y2="43.18" width="0.254" layer="94"/>
<wire x1="-17.78" y1="43.18" x2="17.78" y2="43.18" width="0.254" layer="94"/>
<wire x1="17.78" y1="43.18" x2="17.78" y2="-43.18" width="0.254" layer="94"/>
<wire x1="17.78" y1="-43.18" x2="-17.78" y2="-43.18" width="0.254" layer="94"/>
<text x="-5.08" y="45.72" size="1.778" layer="95">&gt;Name</text>
<text x="-5.08" y="-45.72" size="1.778" layer="96">&gt;Value</text>
<pin name="PA8" x="22.86" y="-20.32" length="middle" rot="R180"/>
<pin name="PA15" x="22.86" y="-2.54" length="middle" rot="R180"/>
<pin name="PB1" x="22.86" y="5.08" length="middle" rot="R180"/>
<pin name="PB2" x="22.86" y="7.62" length="middle" rot="R180"/>
<pin name="PB3" x="22.86" y="10.16" length="middle" rot="R180"/>
<pin name="PB4" x="22.86" y="12.7" length="middle" rot="R180"/>
<pin name="PB5" x="22.86" y="15.24" length="middle" rot="R180"/>
<pin name="PB6" x="22.86" y="17.78" length="middle" rot="R180"/>
<pin name="PB7" x="22.86" y="20.32" length="middle" rot="R180"/>
<pin name="PA11" x="22.86" y="-12.7" length="middle" rot="R180"/>
<pin name="PA12" x="22.86" y="-10.16" length="middle" rot="R180"/>
<pin name="PB8" x="22.86" y="22.86" length="middle" rot="R180"/>
<pin name="PB9" x="22.86" y="25.4" length="middle" rot="R180"/>
<pin name="PB10" x="22.86" y="27.94" length="middle" rot="R180"/>
<pin name="PB11" x="22.86" y="30.48" length="middle" rot="R180"/>
<pin name="PB12" x="22.86" y="33.02" length="middle" rot="R180"/>
<pin name="PB13" x="22.86" y="35.56" length="middle" rot="R180"/>
<pin name="PB14" x="22.86" y="38.1" length="middle" rot="R180"/>
<pin name="PB15" x="22.86" y="40.64" length="middle" rot="R180"/>
<pin name="PC13" x="-22.86" y="2.54" length="middle"/>
<pin name="PC14" x="-22.86" y="5.08" length="middle"/>
<pin name="PC15" x="-22.86" y="7.62" length="middle"/>
<pin name="VSSA" x="-22.86" y="-33.02" length="middle" direction="pwr"/>
<pin name="VBAT" x="-22.86" y="-27.94" length="middle" direction="pwr"/>
<pin name="VDD" x="-22.86" y="-25.4" length="middle"/>
</symbol>
<symbol name="LSM6DS3">
<pin name="SA0" x="12.7" y="10.16" length="middle" rot="R180"/>
<pin name="SDX" x="12.7" y="5.08" length="middle" rot="R180"/>
<pin name="SCX" x="12.7" y="0" length="middle" rot="R180"/>
<pin name="INT1" x="12.7" y="-5.08" length="middle" rot="R180"/>
<pin name="GND" x="12.7" y="-10.16" length="middle" rot="R180"/>
<pin name="VDD" x="-12.7" y="-10.16" length="middle"/>
<pin name="INT2" x="-12.7" y="-5.08" length="middle"/>
<pin name="CS" x="-12.7" y="0" length="middle"/>
<pin name="SCL" x="-12.7" y="5.08" length="middle"/>
<pin name="SDA" x="-12.7" y="10.16" length="middle"/>
<wire x1="-7.62" y1="12.7" x2="-7.62" y2="-12.7" width="0.254" layer="94"/>
<wire x1="-7.62" y1="-12.7" x2="7.62" y2="-12.7" width="0.254" layer="94"/>
<wire x1="7.62" y1="-12.7" x2="7.62" y2="12.7" width="0.254" layer="94"/>
<wire x1="7.62" y1="12.7" x2="-7.62" y2="12.7" width="0.254" layer="94"/>
<text x="-5.08" y="12.7" size="2.1844" layer="95">&gt;NAME</text>
</symbol>
<symbol name="BME280C">
<pin name="SDO" x="-12.7" y="0" length="middle"/>
<pin name="CSB" x="12.7" y="0" length="middle" rot="R180"/>
<pin name="GND" x="12.7" y="5.08" length="middle" rot="R180"/>
<pin name="SDI" x="12.7" y="-5.08" length="middle" rot="R180"/>
<pin name="SCK" x="-12.7" y="-5.08" length="middle"/>
<pin name="VDD" x="-12.7" y="5.08" length="middle"/>
<wire x1="-7.62" y1="7.62" x2="7.62" y2="7.62" width="0.254" layer="94"/>
<wire x1="7.62" y1="7.62" x2="7.62" y2="-7.62" width="0.254" layer="94"/>
<wire x1="7.62" y1="-7.62" x2="-7.62" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-7.62" y1="-7.62" x2="-7.62" y2="7.62" width="0.254" layer="94"/>
<text x="-5.08" y="10.16" size="2.286" layer="94" font="vector">&gt;NAME</text>
</symbol>
<symbol name="GOOUUUATGM336H">
<pin name="GND" x="7.62" y="2.54" length="middle" rot="R180"/>
<pin name="TX" x="7.62" y="-2.54" length="middle" rot="R180"/>
<pin name="VCC" x="7.62" y="7.62" length="middle" rot="R180"/>
<pin name="RX" x="7.62" y="-7.62" length="middle" rot="R180"/>
<wire x1="2.54" y1="10.16" x2="2.54" y2="-10.16" width="0.254" layer="94"/>
<wire x1="2.54" y1="-10.16" x2="-25.4" y2="-10.16" width="0.254" layer="94"/>
<wire x1="-25.4" y1="-10.16" x2="-25.4" y2="10.16" width="0.254" layer="94"/>
<wire x1="-25.4" y1="10.16" x2="2.54" y2="10.16" width="0.254" layer="94"/>
<wire x1="-22.86" y1="7.62" x2="-22.86" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-22.86" y1="-7.62" x2="-5.08" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-7.62" x2="-5.08" y2="7.62" width="0.254" layer="94"/>
<wire x1="-5.08" y1="7.62" x2="-22.86" y2="7.62" width="0.254" layer="94"/>
<text x="-17.78" y="12.7" size="2.54" layer="94" font="vector">&gt;NAME</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="STM32F103C*T" prefix="IC">
<description>&lt;b&gt;ARM 32-bit Cortex™-M3 CPU&lt;/b&gt;&lt;p&gt;
72 MHz maximum frequency&lt;br&gt;
16 to 128 Kbytes of Flash memory&lt;br&gt;
6 to 20 kbytes of SRAM&lt;br&gt;
37 GPIOs&lt;br&gt;
2.0 to 3.6 V application supply&lt;br&gt;</description>
<gates>
<gate name="MCU" symbol="STM32_48PIN_TYP3" x="0" y="0"/>
</gates>
<devices>
<device name="" package="LQFP48">
<connects>
<connect gate="MCU" pin="BOOT0" pad="44"/>
<connect gate="MCU" pin="NRST" pad="7"/>
<connect gate="MCU" pin="OSC_IN" pad="5"/>
<connect gate="MCU" pin="OSC_OUT" pad="6"/>
<connect gate="MCU" pin="PA0-WKUP" pad="10"/>
<connect gate="MCU" pin="PA1" pad="11"/>
<connect gate="MCU" pin="PA10" pad="31"/>
<connect gate="MCU" pin="PA11" pad="32"/>
<connect gate="MCU" pin="PA12" pad="33"/>
<connect gate="MCU" pin="PA13" pad="34"/>
<connect gate="MCU" pin="PA14" pad="37"/>
<connect gate="MCU" pin="PA15" pad="38"/>
<connect gate="MCU" pin="PA2" pad="12"/>
<connect gate="MCU" pin="PA3" pad="13"/>
<connect gate="MCU" pin="PA4" pad="14"/>
<connect gate="MCU" pin="PA5" pad="15"/>
<connect gate="MCU" pin="PA6" pad="16"/>
<connect gate="MCU" pin="PA7" pad="17"/>
<connect gate="MCU" pin="PA8" pad="29"/>
<connect gate="MCU" pin="PA9" pad="30"/>
<connect gate="MCU" pin="PB0" pad="18"/>
<connect gate="MCU" pin="PB1" pad="19"/>
<connect gate="MCU" pin="PB10" pad="21"/>
<connect gate="MCU" pin="PB11" pad="22"/>
<connect gate="MCU" pin="PB12" pad="25"/>
<connect gate="MCU" pin="PB13" pad="26"/>
<connect gate="MCU" pin="PB14" pad="27"/>
<connect gate="MCU" pin="PB15" pad="28"/>
<connect gate="MCU" pin="PB2" pad="20"/>
<connect gate="MCU" pin="PB3" pad="39"/>
<connect gate="MCU" pin="PB4" pad="40"/>
<connect gate="MCU" pin="PB5" pad="41"/>
<connect gate="MCU" pin="PB6" pad="42"/>
<connect gate="MCU" pin="PB7" pad="43"/>
<connect gate="MCU" pin="PB8" pad="45"/>
<connect gate="MCU" pin="PB9" pad="46"/>
<connect gate="MCU" pin="PC13" pad="2"/>
<connect gate="MCU" pin="PC14" pad="3"/>
<connect gate="MCU" pin="PC15" pad="4"/>
<connect gate="MCU" pin="VBAT" pad="1"/>
<connect gate="MCU" pin="VDD" pad="24 36 48"/>
<connect gate="MCU" pin="VDDA" pad="9"/>
<connect gate="MCU" pin="VSSA" pad="8 23 35 47"/>
</connects>
<technologies>
<technology name="4"/>
<technology name="6"/>
<technology name="8"/>
<technology name="B"/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="LSM6DS3">
<gates>
<gate name="G$1" symbol="LSM6DS3" x="0" y="0"/>
</gates>
<devices>
<device name="" package="LGA-14">
<connects>
<connect gate="G$1" pin="CS" pad="P$12"/>
<connect gate="G$1" pin="GND" pad="P$6 P$7"/>
<connect gate="G$1" pin="INT1" pad="P$4"/>
<connect gate="G$1" pin="INT2" pad="P$9"/>
<connect gate="G$1" pin="SA0" pad="P$1"/>
<connect gate="G$1" pin="SCL" pad="P$13"/>
<connect gate="G$1" pin="SCX" pad="P$3"/>
<connect gate="G$1" pin="SDA" pad="P$14"/>
<connect gate="G$1" pin="SDX" pad="P$2"/>
<connect gate="G$1" pin="VDD" pad="P$5 P$8" route="any"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="BME280CHIP">
<gates>
<gate name="BME280" symbol="BME280C" x="0" y="0"/>
</gates>
<devices>
<device name="" package="BME280C">
<connects>
<connect gate="BME280" pin="CSB" pad="2"/>
<connect gate="BME280" pin="GND" pad="1 7"/>
<connect gate="BME280" pin="SCK" pad="4"/>
<connect gate="BME280" pin="SDI" pad="3"/>
<connect gate="BME280" pin="SDO" pad="5"/>
<connect gate="BME280" pin="VDD" pad="6 8"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="GOOUUUATGM336H">
<gates>
<gate name="GOOUUUATGM336H" symbol="GOOUUUATGM336H" x="0" y="0"/>
</gates>
<devices>
<device name="" package="GOOUUUATGM336H">
<connects>
<connect gate="GOOUUUATGM336H" pin="GND" pad="2"/>
<connect gate="GOOUUUATGM336H" pin="RX" pad="4"/>
<connect gate="GOOUUUATGM336H" pin="TX" pad="3"/>
<connect gate="GOOUUUATGM336H" pin="VCC" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="pinhead" urn="urn:adsk.eagle:library:325">
<description>&lt;b&gt;Pin Header Connectors&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="1X02" urn="urn:adsk.eagle:footprint:22309/1" library_version="4">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-1.905" y1="1.27" x2="-0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="-0.635" x2="-0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="1.27" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-1.27" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="1.27" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<pad name="1" x="-1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<text x="-2.6162" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.54" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-1.524" y1="-0.254" x2="-1.016" y2="0.254" layer="51"/>
<rectangle x1="1.016" y1="-0.254" x2="1.524" y2="0.254" layer="51"/>
</package>
<package name="1X02/90" urn="urn:adsk.eagle:footprint:22310/1" library_version="4">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-2.54" y1="-1.905" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.905" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="6.985" x2="-1.27" y2="1.27" width="0.762" layer="21"/>
<wire x1="0" y1="-1.905" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="6.985" x2="1.27" y2="1.27" width="0.762" layer="21"/>
<pad name="1" x="-1.27" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="1.27" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<text x="-3.175" y="-3.81" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="4.445" y="-3.81" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<rectangle x1="-1.651" y1="0.635" x2="-0.889" y2="1.143" layer="21"/>
<rectangle x1="0.889" y1="0.635" x2="1.651" y2="1.143" layer="21"/>
<rectangle x1="-1.651" y1="-2.921" x2="-0.889" y2="-1.905" layer="21"/>
<rectangle x1="0.889" y1="-2.921" x2="1.651" y2="-1.905" layer="21"/>
</package>
</packages>
<packages3d>
<package3d name="1X02" urn="urn:adsk.eagle:package:22435/2" type="model" library_version="4">
<description>PIN HEADER</description>
<packageinstances>
<packageinstance name="1X02"/>
</packageinstances>
</package3d>
<package3d name="1X02/90" urn="urn:adsk.eagle:package:22437/2" type="model" library_version="4">
<description>PIN HEADER</description>
<packageinstances>
<packageinstance name="1X02/90"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="PINHD2" urn="urn:adsk.eagle:symbol:22308/1" library_version="4">
<wire x1="-6.35" y1="-2.54" x2="1.27" y2="-2.54" width="0.4064" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="1.27" y2="5.08" width="0.4064" layer="94"/>
<wire x1="1.27" y1="5.08" x2="-6.35" y2="5.08" width="0.4064" layer="94"/>
<wire x1="-6.35" y1="5.08" x2="-6.35" y2="-2.54" width="0.4064" layer="94"/>
<text x="-6.35" y="5.715" size="1.778" layer="95">&gt;NAME</text>
<text x="-6.35" y="-5.08" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-2.54" y="2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="2" x="-2.54" y="0" visible="pad" length="short" direction="pas" function="dot"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="PINHD-1X2" urn="urn:adsk.eagle:component:22516/4" prefix="JP" uservalue="yes" library_version="4">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="PINHD2" x="0" y="0"/>
</gates>
<devices>
<device name="" package="1X02">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:22435/2"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="POPULARITY" value="98" constant="no"/>
</technology>
</technologies>
</device>
<device name="/90" package="1X02/90">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:22437/2"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="POPULARITY" value="24" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="STM32F103C8T" library="CanCubeSat" deviceset="STM32F103C*T" device="" technology="8"/>
<part name="LSM6DS3" library="CanCubeSat" deviceset="LSM6DS3" device=""/>
<part name="SUPPLY" library="pinhead" library_urn="urn:adsk.eagle:library:325" deviceset="PINHD-1X2" device="" package3d_urn="urn:adsk.eagle:package:22435/2"/>
<part name="TOMOM" library="pinhead" library_urn="urn:adsk.eagle:library:325" deviceset="PINHD-1X2" device="" package3d_urn="urn:adsk.eagle:package:22435/2"/>
<part name="BME280" library="CanCubeSat" deviceset="BME280CHIP" device=""/>
<part name="GOOUUUATGM336H" library="CanCubeSat" deviceset="GOOUUUATGM336H" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="STM32F103C8T" gate="MCU" x="0" y="0" smashed="yes">
<attribute name="NAME" x="-5.08" y="45.72" size="1.778" layer="95"/>
<attribute name="VALUE" x="-5.08" y="-45.72" size="1.778" layer="96"/>
</instance>
<instance part="LSM6DS3" gate="G$1" x="-154.94" y="-2.54" smashed="yes">
<attribute name="NAME" x="-160.02" y="10.16" size="2.1844" layer="95"/>
</instance>
<instance part="SUPPLY" gate="G$1" x="111.76" y="0" smashed="yes">
<attribute name="NAME" x="105.41" y="5.715" size="1.778" layer="95"/>
<attribute name="VALUE" x="105.41" y="-5.08" size="1.778" layer="96"/>
</instance>
<instance part="TOMOM" gate="G$1" x="111.76" y="38.1" smashed="yes">
<attribute name="NAME" x="105.41" y="43.815" size="1.778" layer="95"/>
<attribute name="VALUE" x="105.41" y="33.02" size="1.778" layer="96"/>
</instance>
<instance part="BME280" gate="BME280" x="-154.94" y="48.26" smashed="yes">
<attribute name="NAME" x="-160.02" y="58.42" size="2.286" layer="94" font="vector"/>
</instance>
<instance part="GOOUUUATGM336H" gate="GOOUUUATGM336H" x="-142.24" y="93.98" smashed="yes">
<attribute name="NAME" x="-160.02" y="106.68" size="2.54" layer="94" font="vector"/>
</instance>
</instances>
<busses>
</busses>
<nets>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports the association of 3D packages
with devices in libraries, schematics, and board files. Those 3D
packages will not be understood (or retained) with this version.
</note>
</compatibility>
</eagle>
