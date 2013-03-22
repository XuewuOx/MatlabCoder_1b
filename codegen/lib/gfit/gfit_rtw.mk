# Copyright 1994-2011 The MathWorks, Inc.
#
# File    : xrt_lcc.tmf
#
# Abstract:
#	Code generation template makefile for building a PC-based, stand-alone
#	real-time version of MATLAB code using generated C code and
#			LCC compiler Version 2.4
#
# 	This makefile attempts to conform to the guidelines specified in the
# 	IEEE Std 1003.2-1992 (POSIX) standard. It is designed to be used
#       with GNU Make (gmake) which is located in matlabroot/bin/win32.
#
# 	Note that this template is automatically customized by the
#	code generation build procedure to create "<model>.mk"
#
#   The following defines can be used to modify the behavior of the
#	build:
#	  OPT_OPTS       - Optimization options. Default is none. To enable
#                          debugging specify as OPT_OPTS=-g4.
#	  OPTS           - User specific compile options.
#	  USER_SRCS      - Additional user sources, such as files needed by
#			   S-functions.
#	  USER_INCLUDES  - Additional include paths
#			   (i.e. USER_INCLUDES="-Iwhere-ever -Iwhere-ever2")
#			   (For Lcc, have a '/'as file seperator before the
#			   file name instead of a '\' .
#			   i.e.,  d:\work\proj1/myfile.c - reqd for 'gmake')
#

#------------------------ Macros read by make_rtw ------------------------------
#
# The following macros are read by the code generation build procedure:
#
#  MAKECMD         - This is the command used to invoke the make utility
#  HOST            - What platform this template makefile is targeted for
#                    (i.e. PC or UNIX)
#  BUILD           - Invoke make from the code generation build procedure
#                    (yes/no)?
#  SYS_TARGET_FILE - Name of system target file.

MAKECMD         = "%MATLAB%\bin\win32\gmake"
SHELL           = cmd
HOST            = PC
BUILD           = yes
SYS_TARGET_FILE = ert.tlc
BUILD_SUCCESS	= *** Created
COMPILER_TOOL_CHAIN = lcc

#---------------------- Tokens expanded by make_rtw ----------------------------
#
# The following tokens, when wrapped with "|>" and "<|" are expanded by the
# code generation build procedure.
#
#  MODEL_NAME          - Name of the Simulink block diagram
#  MODEL_MODULES       - Any additional generated source modules
#  MAKEFILE_NAME       - Name of makefile created from template makefile <model>.mk
#  MATLAB_ROOT         - Path to where MATLAB is installed.
#  MATLAB_BIN          - Path to MATLAB executable.
#  S_FUNCTIONS         - List of S-functions.
#  S_FUNCTIONS_LIB     - List of S-functions libraries to link.
#  SOLVER              - Solver source file name
#  NUMST               - Number of sample times
#  TID01EQ             - yes (1) or no (0): Are sampling rates of continuous task
#                        (tid=0) and 1st discrete task equal.
#  NCSTATES            - Number of continuous states
#  BUILDARGS           - Options passed in at the command line.
#  MULTITASKING        - yes (1) or no (0): Is solver mode multitasking
#  EXT_MODE            - yes (1) or no (0): Build for external mode
#  TMW_EXTMODE_TESTING - yes (1) or no (0): Build ext_test.c for external mode
#                        testing.
#  EXTMODE_TRANSPORT   - Index of transport mechanism (e.g. tcpip, serial) for extmode
#  EXTMODE_STATIC      - yes (1) or no (0): Use static instead of dynamic mem alloc.
#  EXTMODE_STATIC_SIZE - Size of static memory allocation buffer.

MODEL                = gfit
MODULES              = gfit_rtwutil.c gfit_initialize.c gfit_terminate.c gfit_rdfile.c mean.c rdivide.c hist.c log.c polyfit.c gfitPDF.c linspace.c meanfile.c std.c gfit_emxutil.c gfit_emxAPI.c rt_nonfinite.c rtGetNaN.c rtGetInf.c 
MAKEFILE             = gfit_rtw.mk
MATLAB_ROOT          = F:\myMatlab2012a
ALT_MATLAB_ROOT      = F:\MYMATL~1
MATLAB_BIN           = F:\myMatlab2012a\bin
ALT_MATLAB_BIN       = F:\MYMATL~1\bin
S_FUNCTIONS          = 
S_FUNCTIONS_LIB      = 
SOLVER               = 
NUMST                = 1
TID01EQ              = 0
NCSTATES             = 0
BUILDARGS            =  GENERATE_REPORT=1 ADD_MDL_NAME_TO_GLOBALS=0
MULTITASKING         = 0
EXT_MODE             = 0
TMW_EXTMODE_TESTING  = 0
EXTMODE_TRANSPORT    = 0
EXTMODE_STATIC       = 0
EXTMODE_STATIC_SIZE  = 1000000

MODELREFS            = 
SHARED_SRC           = 
SHARED_SRC_DIR       = 
SHARED_BIN_DIR       = 
SHARED_LIB           = 
OPTIMIZATION_FLAGS   = 
ADDITIONAL_LDFLAGS   = 

#--------------------------- Model and reference models -----------------------
MODELLIB                  = gfit.lib
MODELREF_LINK_LIBS        = 
MODELREF_LINK_RSPFILE     = gfit_ref.rsp
MODELREF_INC_PATH         = 
RELATIVE_PATH_TO_ANCHOR   = E:\Beagle\ECLIPS~1\MATLAB~2
# NONE: standalone, SIM: modelref sim, RTW: modelref code-generation
MODELREF_TARGET_TYPE       = rtw:lib

#-- In the case when directory name contains space ---
ifneq ($(MATLAB_ROOT),$(ALT_MATLAB_ROOT))
MATLAB_ROOT := $(ALT_MATLAB_ROOT)
endif
ifneq ($(MATLAB_BIN),$(ALT_MATLAB_BIN))
MATLAB_BIN := $(ALT_MATLAB_BIN)
endif

#--------------------------- Tool Specifications ------------------------------

LCC = $(subst \,\\,$(MATLAB_ROOT)\sys\lcc)
include $(MATLAB_ROOT)\rtw\c\tools\lcctools.mak

#----------------------------- External mode -----------------------------------

# Uncomment -DVERBOSE to have information printed to stdout
# To add a new transport layer, see the comments in
#   <matlabroot>/toolbox/simulink/simulink/extmode_transports.m
ifeq ($(EXT_MODE),1)
  EXT_CC_OPTS = -DEXT_MODE -DWIN32 # -DVERBOSE
  ifeq ($(EXTMODE_TRANSPORT),0) #tcpip
    EXT_SRC = ext_svr.c updown.c ext_work.c rtiostream_interface.c rtiostream_tcpip.c
    EXT_LIB = $(MATLAB_ROOT)\sys\lcc\lib\wsock32.lib
  endif
  ifeq ($(EXTMODE_TRANSPORT),1) #serial_win32
    EXT_SRC  = ext_svr.c updown.c ext_work.c ext_svr_serial_transport.c
    EXT_SRC += ext_serial_pkt.c rtiostream_serial_interface.c rtiostream_serial.c
  endif
  ifeq ($(TMW_EXTMODE_TESTING),1)
    EXT_SRC     += ext_test.c
    EXT_CC_OPTS += -DTMW_EXTMODE_TESTING
  endif
  ifeq ($(EXTMODE_STATIC),1)
    EXT_SRC     += mem_mgr.c
    EXT_CC_OPTS += -DEXTMODE_STATIC -DEXTMODE_STATIC_SIZE=$(EXTMODE_STATIC_SIZE)
  endif
endif

#------------------------------ Include Path ----------------------------------

# see MATLAB_INCLUDES and COMPILER_INCLUDES from lcctools.mak

ADD_INCLUDES = \
	-IE:\Beagle\Eclipseworkspace\MatlabCoder_1b\codegen\lib\gfit \
	-IE:\Beagle\Eclipseworkspace\MatlabCoder_1b \


SHARED_INCLUDES =
ifneq ($(SHARED_SRC_DIR),)
SHARED_INCLUDES = -I$(SHARED_SRC_DIR) 
endif

INCLUDES = -I. -I$(RELATIVE_PATH_TO_ANCHOR) $(MATLAB_INCLUDES) $(ADD_INCLUDES) \
           $(COMPILER_INCLUDES) $(USER_INCLUDES) $(MODELREF_INC_PATH) $(SHARED_INCLUDES)

#------------------------ rtModel ----------------------------------------------
RTM_CC_OPTS = -DUSE_RTMODEL

#-------------------------------- C Flags --------------------------------------

# Optimization Options
OPT_OPTS = $(DEFAULT_OPT_OPTS)

# General User Options
OPTS =

# Compiler options, etc:
ifneq ($(OPTIMIZATION_FLAGS),)
CC_OPTS = $(OPTS) $(ANSI_OPTS) $(EXT_CC_OPTS) $(RTM_CC_OPTS) $(OPTIMIZATION_FLAGS)
else
CC_OPTS = $(OPT_OPTS) $(OPTS) $(ANSI_OPTS) $(EXT_CC_OPTS) $(RTM_CC_OPTS)
endif

CPP_REQ_DEFINES = -DMODEL=$(MODEL) -DRT -DNUMST=$(NUMST) \
                  -DTID01EQ=$(TID01EQ) -DNCSTATES=$(NCSTATES) \
                  -DMT=$(MULTITASKING) -DHAVESTDIO 

CFLAGS = $(CC_OPTS) $(CPP_REQ_DEFINES) $(INCLUDES) -noregistrylookup

ifeq ($(OPT_OPTS),$(DEFAULT_OPT_OPTS))
LDFLAGS = -s -L$(LIB)
else
LDFLAGS = -L$(LIB)
endif

#------------------------- Additional Libraries -------------------------------

LIBS =


LIBS += $(EXT_LIB) $(S_FUNCTIONS_LIB)

LCCSTUB = $(MODEL)_lccstub.obj

#----------------------------- Source Files ------------------------------------

ifeq ($(MODELREF_TARGET_TYPE), NONE)
    # Executable code generation target
    PRODUCT            = $(RELATIVE_PATH_TO_ANCHOR)/$(MODEL).exe
    BIN_SETTING        = $(LD) $(LDFLAGS) $(ADDITIONAL_LDFLAGS) -o $(PRODUCT) $(SYSLIBS)
    BUILD_PRODUCT_TYPE = executable
    REQ_SRCS           = $(MODULES) $(EXT_SRC)
else ifeq ($(MODELREF_TARGET_TYPE), rtw:dll)
    # Shared library code generation target
    PRODUCT  = $(MODELLIB)
    REQ_SRCS = $(MODULES)
    BIN_SETTING = $(LD) -dll $(LDFLAGS) $(ADDITIONAL_LDFLAGS) -o $(PRODUCT) $(MODEL)_dll.def $(LCCSTUB)
else
    # Static library code generation target
    PRODUCT  = $(MODELLIB)
    REQ_SRCS = $(MODULES)
endif

USER_SRCS =

USER_OBJS       = $(USER_SRCS:.c=.obj)
LOCAL_USER_OBJS = $(notdir $(USER_OBJS))

SRCS      = $(REQ_SRCS) $(S_FUNCTIONS) $(SOLVER)
OBJS      = $(SRCS:.c=.obj)  $(USER_OBJS)
LINK_OBJS = $(SRCS:.c=.obj) $(LOCAL_USER_OBJS)

SHARED_OBJS := $(addsuffix .obj, $(basename $(wildcard $(SHARED_SRC))))
FMT_SHARED_OBJS = $(subst /,\,$(SHARED_OBJS))

#--------------------------------- Rules ---------------------------------------

ifeq ($(MODELREF_TARGET_TYPE),NONE)
$(PRODUCT) : $(OBJS) $(SHARED_LIB) $(LIBS) $(MODELREF_LINK_LIBS)
	$(BIN_SETTING) $(LINK_OBJS) @$(MODELREF_LINK_RSPFILE) $(SHARED_LIB) $(LIBS) 
	@cmd /C "echo $(BUILD_SUCCESS) executable: $(MODEL).exe"
else ifeq ($(MODELREF_TARGET_TYPE), rtw:dll)
#--- Shared library target ---
$(PRODUCT) : $(OBJS) $(SHARED_LIB) $(LCCSTUB)
	$(BIN_SETTING) $(LINK_OBJS) @$(MODELREF_LINK_RSPFILE) $(SHARED_LIB) $(LIBS) 
	@cmd /C "echo $(BUILD_SUCCESS) shared library $(PRODUCT)"
else
#--- Static library target ---
$(PRODUCT) : $(OBJS) $(SHARED_LIB)
	@if exist $(MODELLIB) del $(MODELLIB)
	$(LIBCMD) /out:$(MODELLIB) $(LINK_OBJS)
	@cmd /C "echo $(BUILD_SUCCESS) static library $(MODELLIB)"
endif

%.obj : %.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) -c -Fo$(@F) -I$(RELATIVE_PATH_TO_ANCHOR)/$(<F:.c=cn_rtw) $(CFLAGS)  $<



# Libraries:





#----------------------------- Dependencies ------------------------------------

$(OBJS) : $(MAKEFILE) rtw_proj.tmw

$(SHARED_OBJS) : $(SHARED_BIN_DIR)/%.obj : $(SHARED_SRC_DIR)/%.c 
	$(CC) -c -Fo$@ $(CFLAGS) $<

$(SHARED_LIB) : $(SHARED_OBJS)
	@cmd /C "echo ### Creating $@"
	@if exist $@ del $@
	$(LIBCMD) /out:$@ $(FMT_SHARED_OBJS)
	@cmd /C "echo ### $@ Created"

$(LCCSTUB) : $(MATLAB_ROOT)\sys\lcc\mex\lccstub.c
	$(CC) -Fo$(LCCSTUB) $(CFLAGS) "$<"

#--------- Miscellaneous rules to purge, clean and lint (sol2 only) ------------

purge : clean
	@cmd /C "echo ### Deleting the generated source code for $(MODEL)"
	@del $(MODEL).c $(MODEL).h $(MODEL)_types.h $(MODEL)_data.c \
	        $(MODEL)_private.h $(MODEL).rtw $(MODULES) rtw_proj.tmw $(MAKEFILE)

clean :
	@cmd /C "echo ### Deleting the objects and $(PROGRAM)"
	@del $(LINK_OBJS) ..\$(MODEL).exe



# EOF: xrt_lcc.tmf
