##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Hunt_the_wumpus
ConfigurationName      :=Debug
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=C:/Users/jvdk_/Documents/codeliteworkspace
ProjectPath            :=C:/Users/jvdk_/Documents/Gameproject
IntermediateDirectory  :=../codeliteworkspace/build-$(ConfigurationName)/__/Gameproject
OutDir                 :=../codeliteworkspace/build-$(ConfigurationName)/__/Gameproject
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=jvdk_
Date                   :=26/03/2020
CodeLitePath           :=C:/Users/jvdk_/Documents/codelite/CodeLite
LinkerName             :=C:/Users/jvdk_/Documents/GCC/bin/g++.exe
SharedObjectLinkerName :=C:/Users/jvdk_/Documents/GCC/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=..\codeliteworkspace\build-$(ConfigurationName)\bin\$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
RcCmpOptions           := 
RcCompilerName         :=C:/Users/jvdk_/Documents/GCC/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/Users/jvdk_/Documents/GCC/bin/ar.exe rcu
CXX      := C:/Users/jvdk_/Documents/GCC/bin/g++.exe
CC       := C:/Users/jvdk_/Documents/GCC/bin/gcc.exe
CXXFLAGS :=  -g -O0 -std=c++14 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/Users/jvdk_/Documents/GCC/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Users\jvdk_\Documents\codelite\CodeLite
Objects0=../codeliteworkspace/build-$(ConfigurationName)/__/Gameproject/main.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ../codeliteworkspace/build-$(ConfigurationName)/__/Gameproject/.d $(Objects) 
	@if not exist "..\codeliteworkspace\build-$(ConfigurationName)\__\Gameproject" mkdir "..\codeliteworkspace\build-$(ConfigurationName)\__\Gameproject"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@if not exist "..\codeliteworkspace\build-$(ConfigurationName)\__\Gameproject" mkdir "..\codeliteworkspace\build-$(ConfigurationName)\__\Gameproject"
	@if not exist ""..\codeliteworkspace\build-$(ConfigurationName)\bin"" mkdir ""..\codeliteworkspace\build-$(ConfigurationName)\bin""

../codeliteworkspace/build-$(ConfigurationName)/__/Gameproject/.d:
	@if not exist "..\codeliteworkspace\build-$(ConfigurationName)\__\Gameproject" mkdir "..\codeliteworkspace\build-$(ConfigurationName)\__\Gameproject"

PreBuild:


##
## Objects
##
../codeliteworkspace/build-$(ConfigurationName)/__/Gameproject/main.cpp$(ObjectSuffix): main.cpp ../codeliteworkspace/build-$(ConfigurationName)/__/Gameproject/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/jvdk_/Documents/Gameproject/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
../codeliteworkspace/build-$(ConfigurationName)/__/Gameproject/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../codeliteworkspace/build-$(ConfigurationName)/__/Gameproject/main.cpp$(ObjectSuffix) -MF../codeliteworkspace/build-$(ConfigurationName)/__/Gameproject/main.cpp$(DependSuffix) -MM main.cpp

../codeliteworkspace/build-$(ConfigurationName)/__/Gameproject/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../codeliteworkspace/build-$(ConfigurationName)/__/Gameproject/main.cpp$(PreprocessSuffix) main.cpp


-include ../codeliteworkspace/build-$(ConfigurationName)/__/Gameproject//*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


