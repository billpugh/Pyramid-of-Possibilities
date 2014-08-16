#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1731549632/AVEAnimation1.o \
	${OBJECTDIR}/_ext/1731549632/ActivityLevelAnimation.o \
	${OBJECTDIR}/_ext/1731549632/Animations.o \
	${OBJECTDIR}/_ext/1731549632/Beacon.o \
	${OBJECTDIR}/_ext/1731549632/ChangingColor.o \
	${OBJECTDIR}/_ext/1731549632/Chasers.o \
	${OBJECTDIR}/_ext/1731549632/CircularGradient.o \
	${OBJECTDIR}/_ext/1731549632/ColorWorms.o \
	${OBJECTDIR}/_ext/1731549632/Constants.o \
	${OBJECTDIR}/_ext/1731549632/DRAnimation1.o \
	${OBJECTDIR}/_ext/1731549632/Explosion.o \
	${OBJECTDIR}/_ext/1731549632/FlashAttack.o \
	${OBJECTDIR}/_ext/1731549632/FlashEcho.o \
	${OBJECTDIR}/_ext/1731549632/Flashes.o \
	${OBJECTDIR}/_ext/1731549632/GlowFade.o \
	${OBJECTDIR}/_ext/1731549632/Kittens.o \
	${OBJECTDIR}/_ext/1731549632/MovingFaces.o \
	${OBJECTDIR}/_ext/1731549632/Mute.o \
	${OBJECTDIR}/_ext/1731549632/Platform.o \
	${OBJECTDIR}/_ext/1731549632/Qbert.o \
	${OBJECTDIR}/_ext/1731549632/RNAnimation.o \
	${OBJECTDIR}/_ext/1731549632/RNBeam.o \
	${OBJECTDIR}/_ext/1731549632/RNComm.o \
	${OBJECTDIR}/_ext/1731549632/RNEEPROM.o \
	${OBJECTDIR}/_ext/1731549632/RNInfo.o \
	${OBJECTDIR}/_ext/1731549632/LiftOff.o \
	${OBJECTDIR}/_ext/1731549632/Radial.o \
	${OBJECTDIR}/_ext/1731549632/SideEffects.o \
	${OBJECTDIR}/_ext/1731549632/Snow.o \
	${OBJECTDIR}/_ext/1731549632/Swirl.o \
	${OBJECTDIR}/_ext/1731549632/WWPAnimationTest.o \
	${OBJECTDIR}/_ext/1731549632/ledPositions.o \
	${OBJECTDIR}/_ext/1926129150/easing.o \
	${OBJECTDIR}/_ext/1926129150/easingSelect.o \
	${OBJECTDIR}/_ext/1989308899/Accelerometer.o \
	${OBJECTDIR}/_ext/1989308899/i2c_t3.o \
	${OBJECTDIR}/_ext/1253334877/hsv2rgb.o \
	${OBJECTDIR}/_ext/1827099284/RNChaser.o \
	${OBJECTDIR}/_ext/1568344763/RNGradient.o \
	${OBJECTDIR}/_ext/1568344763/RNLights.o \
	${OBJECTDIR}/_ext/1371306724/RNSerial.o \
	${OBJECTDIR}/Arduino.o \
	${OBJECTDIR}/FPSControlsHandler.o \
	${OBJECTDIR}/PlatformControler.o \
	${OBJECTDIR}/Pyramid.o \
	${OBJECTDIR}/PyramidArchitecture.o \
	${OBJECTDIR}/RNLightsSimulator.o \
	${OBJECTDIR}/ShaderLoader.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-Wno-write-strings
CXXFLAGS=-Wno-write-strings

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS= -L/usr/local/lib -framework OpenGL

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/popsimulator

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/popsimulator: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/popsimulator ${OBJECTFILES} ${LDLIBSOPTIONS}  -lglfw3 -lGLEW

${OBJECTDIR}/_ext/1731549632/AVEAnimation1.o: ../Arduino/PyramidOfPossibilities/AVEAnimation1.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/AVEAnimation1.o ../Arduino/PyramidOfPossibilities/AVEAnimation1.cpp

${OBJECTDIR}/_ext/1731549632/ActivityLevelAnimation.o: ../Arduino/PyramidOfPossibilities/ActivityLevelAnimation.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/ActivityLevelAnimation.o ../Arduino/PyramidOfPossibilities/ActivityLevelAnimation.cpp

${OBJECTDIR}/_ext/1731549632/Animations.o: ../Arduino/PyramidOfPossibilities/Animations.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/Animations.o ../Arduino/PyramidOfPossibilities/Animations.cpp

${OBJECTDIR}/_ext/1731549632/Beacon.o: ../Arduino/PyramidOfPossibilities/Beacon.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/Beacon.o ../Arduino/PyramidOfPossibilities/Beacon.cpp

${OBJECTDIR}/_ext/1731549632/ChangingColor.o: ../Arduino/PyramidOfPossibilities/ChangingColor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/ChangingColor.o ../Arduino/PyramidOfPossibilities/ChangingColor.cpp

${OBJECTDIR}/_ext/1731549632/Chasers.o: ../Arduino/PyramidOfPossibilities/Chasers.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/Chasers.o ../Arduino/PyramidOfPossibilities/Chasers.cpp

${OBJECTDIR}/_ext/1731549632/CircularGradient.o: ../Arduino/PyramidOfPossibilities/CircularGradient.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/CircularGradient.o ../Arduino/PyramidOfPossibilities/CircularGradient.cpp

${OBJECTDIR}/_ext/1731549632/ColorWorms.o: ../Arduino/PyramidOfPossibilities/ColorWorms.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/ColorWorms.o ../Arduino/PyramidOfPossibilities/ColorWorms.cpp

${OBJECTDIR}/_ext/1731549632/Constants.o: ../Arduino/PyramidOfPossibilities/Constants.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/Constants.o ../Arduino/PyramidOfPossibilities/Constants.cpp

${OBJECTDIR}/_ext/1731549632/DRAnimation1.o: ../Arduino/PyramidOfPossibilities/DRAnimation1.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/DRAnimation1.o ../Arduino/PyramidOfPossibilities/DRAnimation1.cpp

${OBJECTDIR}/_ext/1731549632/Explosion.o: ../Arduino/PyramidOfPossibilities/Explosion.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/Explosion.o ../Arduino/PyramidOfPossibilities/Explosion.cpp

${OBJECTDIR}/_ext/1731549632/FlashAttack.o: ../Arduino/PyramidOfPossibilities/FlashAttack.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/FlashAttack.o ../Arduino/PyramidOfPossibilities/FlashAttack.cpp

${OBJECTDIR}/_ext/1731549632/FlashEcho.o: ../Arduino/PyramidOfPossibilities/FlashEcho.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/FlashEcho.o ../Arduino/PyramidOfPossibilities/FlashEcho.cpp

${OBJECTDIR}/_ext/1731549632/Flashes.o: ../Arduino/PyramidOfPossibilities/Flashes.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/Flashes.o ../Arduino/PyramidOfPossibilities/Flashes.cpp

${OBJECTDIR}/_ext/1731549632/GlowFade.o: ../Arduino/PyramidOfPossibilities/GlowFade.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/GlowFade.o ../Arduino/PyramidOfPossibilities/GlowFade.cpp

${OBJECTDIR}/_ext/1731549632/Kittens.o: ../Arduino/PyramidOfPossibilities/Kittens.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/Kittens.o ../Arduino/PyramidOfPossibilities/Kittens.cpp

${OBJECTDIR}/_ext/1731549632/MovingFaces.o: ../Arduino/PyramidOfPossibilities/MovingFaces.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/MovingFaces.o ../Arduino/PyramidOfPossibilities/MovingFaces.cpp

${OBJECTDIR}/_ext/1731549632/Mute.o: ../Arduino/PyramidOfPossibilities/Mute.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/Mute.o ../Arduino/PyramidOfPossibilities/Mute.cpp

${OBJECTDIR}/_ext/1731549632/Platform.o: ../Arduino/PyramidOfPossibilities/Platform.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/Platform.o ../Arduino/PyramidOfPossibilities/Platform.cpp

${OBJECTDIR}/_ext/1731549632/Qbert.o: ../Arduino/PyramidOfPossibilities/Qbert.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/Qbert.o ../Arduino/PyramidOfPossibilities/Qbert.cpp

${OBJECTDIR}/_ext/1731549632/RNAnimation.o: ../Arduino/PyramidOfPossibilities/RNAnimation.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/RNAnimation.o ../Arduino/PyramidOfPossibilities/RNAnimation.cpp

${OBJECTDIR}/_ext/1731549632/RNBeam.o: ../Arduino/PyramidOfPossibilities/RNBeam.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/RNBeam.o ../Arduino/PyramidOfPossibilities/RNBeam.cpp

${OBJECTDIR}/_ext/1731549632/RNComm.o: ../Arduino/PyramidOfPossibilities/RNComm.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/RNComm.o ../Arduino/PyramidOfPossibilities/RNComm.cpp

${OBJECTDIR}/_ext/1731549632/RNEEPROM.o: ../Arduino/PyramidOfPossibilities/RNEEPROM.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/RNEEPROM.o ../Arduino/PyramidOfPossibilities/RNEEPROM.cpp

${OBJECTDIR}/_ext/1731549632/RNInfo.o: ../Arduino/PyramidOfPossibilities/RNInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/RNInfo.o ../Arduino/PyramidOfPossibilities/RNInfo.cpp

${OBJECTDIR}/_ext/1731549632/LiftOff.o: ../Arduino/PyramidOfPossibilities/LiftOff.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/LiftOff.o ../Arduino/PyramidOfPossibilities/LiftOff.cpp

${OBJECTDIR}/_ext/1731549632/Radial.o: ../Arduino/PyramidOfPossibilities/Radial.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/Radial.o ../Arduino/PyramidOfPossibilities/Radial.cpp

${OBJECTDIR}/_ext/1731549632/SideEffects.o: ../Arduino/PyramidOfPossibilities/SideEffects.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/SideEffects.o ../Arduino/PyramidOfPossibilities/SideEffects.cpp

${OBJECTDIR}/_ext/1731549632/Snow.o: ../Arduino/PyramidOfPossibilities/Snow.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/Snow.o ../Arduino/PyramidOfPossibilities/Snow.cpp

${OBJECTDIR}/_ext/1731549632/Swirl.o: ../Arduino/PyramidOfPossibilities/Swirl.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/Swirl.o ../Arduino/PyramidOfPossibilities/Swirl.cpp

${OBJECTDIR}/_ext/1731549632/WWPAnimationTest.o: ../Arduino/PyramidOfPossibilities/WWPAnimationTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/WWPAnimationTest.o ../Arduino/PyramidOfPossibilities/WWPAnimationTest.cpp

${OBJECTDIR}/_ext/1731549632/ledPositions.o: ../Arduino/PyramidOfPossibilities/ledPositions.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/ledPositions.o ../Arduino/PyramidOfPossibilities/ledPositions.cpp

${OBJECTDIR}/_ext/1926129150/easing.o: ../Arduino/libraries/AHEasing/easing.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926129150
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1926129150/easing.o ../Arduino/libraries/AHEasing/easing.cpp

${OBJECTDIR}/_ext/1926129150/easingSelect.o: ../Arduino/libraries/AHEasing/easingSelect.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926129150
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1926129150/easingSelect.o ../Arduino/libraries/AHEasing/easingSelect.cpp

${OBJECTDIR}/_ext/1989308899/Accelerometer.o: ../Arduino/libraries/Accelerometer/Accelerometer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1989308899
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1989308899/Accelerometer.o ../Arduino/libraries/Accelerometer/Accelerometer.cpp

${OBJECTDIR}/_ext/1989308899/i2c_t3.o: ../Arduino/libraries/Accelerometer/i2c_t3.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1989308899
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1989308899/i2c_t3.o ../Arduino/libraries/Accelerometer/i2c_t3.cpp

${OBJECTDIR}/_ext/1253334877/hsv2rgb.o: ../Arduino/libraries/FastLED/hsv2rgb.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1253334877
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1253334877/hsv2rgb.o ../Arduino/libraries/FastLED/hsv2rgb.cpp

${OBJECTDIR}/_ext/1827099284/RNChaser.o: ../Arduino/libraries/RNChaser/RNChaser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1827099284
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1827099284/RNChaser.o ../Arduino/libraries/RNChaser/RNChaser.cpp

${OBJECTDIR}/_ext/1568344763/RNGradient.o: ../Arduino/libraries/RNLights/RNGradient.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1568344763
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1568344763/RNGradient.o ../Arduino/libraries/RNLights/RNGradient.cpp

${OBJECTDIR}/_ext/1568344763/RNLights.o: ../Arduino/libraries/RNLights/RNLights.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1568344763
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1568344763/RNLights.o ../Arduino/libraries/RNLights/RNLights.cpp

${OBJECTDIR}/_ext/1371306724/RNSerial.o: ../Arduino/libraries/RNSerial/RNSerial.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1371306724
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1371306724/RNSerial.o ../Arduino/libraries/RNSerial/RNSerial.cpp

${OBJECTDIR}/Arduino.o: Arduino.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Arduino.o Arduino.c

${OBJECTDIR}/FPSControlsHandler.o: FPSControlsHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FPSControlsHandler.o FPSControlsHandler.cpp

${OBJECTDIR}/PlatformControler.o: PlatformControler.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PlatformControler.o PlatformControler.cpp

${OBJECTDIR}/Pyramid.o: Pyramid.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Pyramid.o Pyramid.cpp

${OBJECTDIR}/PyramidArchitecture.o: PyramidArchitecture.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PyramidArchitecture.o PyramidArchitecture.cpp

${OBJECTDIR}/RNLightsSimulator.o: RNLightsSimulator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/RNLightsSimulator.o RNLightsSimulator.cpp

${OBJECTDIR}/ShaderLoader.o: ShaderLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ShaderLoader.o ShaderLoader.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Arduino/PyramidOfPossibilities -I../PlatformData -I../Arduino/libraries/RNChaser -I../Arduino/libraries/RNLights -I../Arduino/libraries/Accelerometer -I../Arduino/PyramidOfPossibilities -I. -I../Arduino/libraries/FastLED -I../Arduino/libraries/AHEasing -I../Arduino/libraries/RNSerial -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/popsimulator

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
