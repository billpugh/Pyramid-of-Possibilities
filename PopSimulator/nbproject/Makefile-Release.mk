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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1731549632/AVEAnimation1.o \
	${OBJECTDIR}/_ext/1731549632/Animations.o \
	${OBJECTDIR}/_ext/1731549632/RNAnimation.o \
	${OBJECTDIR}/_ext/1731549632/RNInfo.o \
	${OBJECTDIR}/_ext/1731549632/WWPAnimation1.o \
	${OBJECTDIR}/_ext/1731549632/WWPAnimation2.o \
	${OBJECTDIR}/_ext/1731549632/WWPAnimation3.o \
	${OBJECTDIR}/_ext/1731549632/WWPAnimation4.o \
	${OBJECTDIR}/_ext/1731549632/WWPAnimation5.o \
	${OBJECTDIR}/_ext/1253334877/hsv2rgb.o \
	${OBJECTDIR}/_ext/1827099284/RNChaser.o \
	${OBJECTDIR}/_ext/1738591540/RNLights.o \
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
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/popsimulator

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/popsimulator: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/popsimulator ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/1731549632/AVEAnimation1.o: ../Arduino/PyramidOfPossibilities/AVEAnimation1.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/AVEAnimation1.o ../Arduino/PyramidOfPossibilities/AVEAnimation1.cpp

${OBJECTDIR}/_ext/1731549632/Animations.o: ../Arduino/PyramidOfPossibilities/Animations.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/Animations.o ../Arduino/PyramidOfPossibilities/Animations.cpp

${OBJECTDIR}/_ext/1731549632/RNAnimation.o: ../Arduino/PyramidOfPossibilities/RNAnimation.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/RNAnimation.o ../Arduino/PyramidOfPossibilities/RNAnimation.cpp

${OBJECTDIR}/_ext/1731549632/RNInfo.o: ../Arduino/PyramidOfPossibilities/RNInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/RNInfo.o ../Arduino/PyramidOfPossibilities/RNInfo.cpp

${OBJECTDIR}/_ext/1731549632/WWPAnimation1.o: ../Arduino/PyramidOfPossibilities/WWPAnimation1.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/WWPAnimation1.o ../Arduino/PyramidOfPossibilities/WWPAnimation1.cpp

${OBJECTDIR}/_ext/1731549632/WWPAnimation2.o: ../Arduino/PyramidOfPossibilities/WWPAnimation2.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/WWPAnimation2.o ../Arduino/PyramidOfPossibilities/WWPAnimation2.cpp

${OBJECTDIR}/_ext/1731549632/WWPAnimation3.o: ../Arduino/PyramidOfPossibilities/WWPAnimation3.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/WWPAnimation3.o ../Arduino/PyramidOfPossibilities/WWPAnimation3.cpp

${OBJECTDIR}/_ext/1731549632/WWPAnimation4.o: ../Arduino/PyramidOfPossibilities/WWPAnimation4.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/WWPAnimation4.o ../Arduino/PyramidOfPossibilities/WWPAnimation4.cpp

${OBJECTDIR}/_ext/1731549632/WWPAnimation5.o: ../Arduino/PyramidOfPossibilities/WWPAnimation5.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1731549632
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1731549632/WWPAnimation5.o ../Arduino/PyramidOfPossibilities/WWPAnimation5.cpp

${OBJECTDIR}/_ext/1253334877/hsv2rgb.o: ../Arduino/libraries/FastLED/hsv2rgb.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1253334877
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1253334877/hsv2rgb.o ../Arduino/libraries/FastLED/hsv2rgb.cpp

${OBJECTDIR}/_ext/1827099284/RNChaser.o: ../Arduino/libraries/RNChaser/RNChaser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1827099284
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1827099284/RNChaser.o ../Arduino/libraries/RNChaser/RNChaser.cpp

${OBJECTDIR}/_ext/1738591540/RNLights.o: ../PlatformData/RNLights.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1738591540
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1738591540/RNLights.o ../PlatformData/RNLights.cpp

${OBJECTDIR}/Arduino.o: Arduino.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Arduino.o Arduino.c

${OBJECTDIR}/FPSControlsHandler.o: FPSControlsHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FPSControlsHandler.o FPSControlsHandler.cpp

${OBJECTDIR}/PlatformControler.o: PlatformControler.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PlatformControler.o PlatformControler.cpp

${OBJECTDIR}/Pyramid.o: Pyramid.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Pyramid.o Pyramid.cpp

${OBJECTDIR}/PyramidArchitecture.o: PyramidArchitecture.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PyramidArchitecture.o PyramidArchitecture.cpp

${OBJECTDIR}/RNLightsSimulator.o: RNLightsSimulator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/RNLightsSimulator.o RNLightsSimulator.cpp

${OBJECTDIR}/ShaderLoader.o: ShaderLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ShaderLoader.o ShaderLoader.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

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
