##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=statmqtt
ConfigurationName      :=Debug
WorkspacePath          := "/home/richard/Source"
ProjectPath            := "/home/richard/Source/statmqtt"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Richard
Date                   :=25/11/16
CodeLitePath           :="/home/richard/.codelite"
LinkerName             :=gcc
SharedObjectLinkerName :=gcc -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="statmqtt.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)/user/local/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)statgrab $(LibrarySwitch)pthread $(LibrarySwitch)paho-mqtt3a $(LibrarySwitch)atasmart 
ArLibs                 :=  "statgrab" "pthread" "paho-mqtt3a" "atasmart" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := gcc
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/mqtt.c$(ObjectSuffix) $(IntermediateDirectory)/cpulog.c$(ObjectSuffix) $(IntermediateDirectory)/vmlog.c$(ObjectSuffix) $(IntermediateDirectory)/utils.c$(ObjectSuffix) $(IntermediateDirectory)/netlinklog.c$(ObjectSuffix) $(IntermediateDirectory)/networklog.c$(ObjectSuffix) $(IntermediateDirectory)/filesystemlog.c$(ObjectSuffix) $(IntermediateDirectory)/smartlog.c$(ObjectSuffix) $(IntermediateDirectory)/misclog.c$(ObjectSuffix) \
	$(IntermediateDirectory)/processlog.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/richard/Source/statmqtt/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM "main.c"

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) "main.c"

$(IntermediateDirectory)/mqtt.c$(ObjectSuffix): mqtt.c $(IntermediateDirectory)/mqtt.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/richard/Source/statmqtt/mqtt.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mqtt.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mqtt.c$(DependSuffix): mqtt.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mqtt.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mqtt.c$(DependSuffix) -MM "mqtt.c"

$(IntermediateDirectory)/mqtt.c$(PreprocessSuffix): mqtt.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mqtt.c$(PreprocessSuffix) "mqtt.c"

$(IntermediateDirectory)/cpulog.c$(ObjectSuffix): cpulog.c $(IntermediateDirectory)/cpulog.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/richard/Source/statmqtt/cpulog.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cpulog.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cpulog.c$(DependSuffix): cpulog.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cpulog.c$(ObjectSuffix) -MF$(IntermediateDirectory)/cpulog.c$(DependSuffix) -MM "cpulog.c"

$(IntermediateDirectory)/cpulog.c$(PreprocessSuffix): cpulog.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cpulog.c$(PreprocessSuffix) "cpulog.c"

$(IntermediateDirectory)/vmlog.c$(ObjectSuffix): vmlog.c $(IntermediateDirectory)/vmlog.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/richard/Source/statmqtt/vmlog.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/vmlog.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/vmlog.c$(DependSuffix): vmlog.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/vmlog.c$(ObjectSuffix) -MF$(IntermediateDirectory)/vmlog.c$(DependSuffix) -MM "vmlog.c"

$(IntermediateDirectory)/vmlog.c$(PreprocessSuffix): vmlog.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/vmlog.c$(PreprocessSuffix) "vmlog.c"

$(IntermediateDirectory)/utils.c$(ObjectSuffix): utils.c $(IntermediateDirectory)/utils.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/richard/Source/statmqtt/utils.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/utils.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/utils.c$(DependSuffix): utils.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/utils.c$(ObjectSuffix) -MF$(IntermediateDirectory)/utils.c$(DependSuffix) -MM "utils.c"

$(IntermediateDirectory)/utils.c$(PreprocessSuffix): utils.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/utils.c$(PreprocessSuffix) "utils.c"

$(IntermediateDirectory)/netlinklog.c$(ObjectSuffix): netlinklog.c $(IntermediateDirectory)/netlinklog.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/richard/Source/statmqtt/netlinklog.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/netlinklog.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/netlinklog.c$(DependSuffix): netlinklog.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/netlinklog.c$(ObjectSuffix) -MF$(IntermediateDirectory)/netlinklog.c$(DependSuffix) -MM "netlinklog.c"

$(IntermediateDirectory)/netlinklog.c$(PreprocessSuffix): netlinklog.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/netlinklog.c$(PreprocessSuffix) "netlinklog.c"

$(IntermediateDirectory)/networklog.c$(ObjectSuffix): networklog.c $(IntermediateDirectory)/networklog.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/richard/Source/statmqtt/networklog.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/networklog.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/networklog.c$(DependSuffix): networklog.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/networklog.c$(ObjectSuffix) -MF$(IntermediateDirectory)/networklog.c$(DependSuffix) -MM "networklog.c"

$(IntermediateDirectory)/networklog.c$(PreprocessSuffix): networklog.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/networklog.c$(PreprocessSuffix) "networklog.c"

$(IntermediateDirectory)/filesystemlog.c$(ObjectSuffix): filesystemlog.c $(IntermediateDirectory)/filesystemlog.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/richard/Source/statmqtt/filesystemlog.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/filesystemlog.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/filesystemlog.c$(DependSuffix): filesystemlog.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/filesystemlog.c$(ObjectSuffix) -MF$(IntermediateDirectory)/filesystemlog.c$(DependSuffix) -MM "filesystemlog.c"

$(IntermediateDirectory)/filesystemlog.c$(PreprocessSuffix): filesystemlog.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/filesystemlog.c$(PreprocessSuffix) "filesystemlog.c"

$(IntermediateDirectory)/smartlog.c$(ObjectSuffix): smartlog.c $(IntermediateDirectory)/smartlog.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/richard/Source/statmqtt/smartlog.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/smartlog.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/smartlog.c$(DependSuffix): smartlog.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/smartlog.c$(ObjectSuffix) -MF$(IntermediateDirectory)/smartlog.c$(DependSuffix) -MM "smartlog.c"

$(IntermediateDirectory)/smartlog.c$(PreprocessSuffix): smartlog.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/smartlog.c$(PreprocessSuffix) "smartlog.c"

$(IntermediateDirectory)/misclog.c$(ObjectSuffix): misclog.c $(IntermediateDirectory)/misclog.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/richard/Source/statmqtt/misclog.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/misclog.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/misclog.c$(DependSuffix): misclog.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/misclog.c$(ObjectSuffix) -MF$(IntermediateDirectory)/misclog.c$(DependSuffix) -MM "misclog.c"

$(IntermediateDirectory)/misclog.c$(PreprocessSuffix): misclog.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/misclog.c$(PreprocessSuffix) "misclog.c"

$(IntermediateDirectory)/processlog.c$(ObjectSuffix): processlog.c $(IntermediateDirectory)/processlog.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/richard/Source/statmqtt/processlog.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/processlog.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/processlog.c$(DependSuffix): processlog.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/processlog.c$(ObjectSuffix) -MF$(IntermediateDirectory)/processlog.c$(DependSuffix) -MM "processlog.c"

$(IntermediateDirectory)/processlog.c$(PreprocessSuffix): processlog.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/processlog.c$(PreprocessSuffix) "processlog.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


