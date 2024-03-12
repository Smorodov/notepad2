cmake_minimum_required (VERSION 3.27)
project (editor C CXX)

# Uncomment below to build and run in Unicode
add_definitions(
-D_WIN32_WINNT=0x0600
-DWINVER=0x0600
-D_WINDOWS
-DNOMINMAX
-DWIN32_LEAN_AND_MEAN
-DSTRICT_TYPED_ITEMIDS
-DNO_CXX11_REGEX
-DUNICODE
-D_UNICODE
-D_CRT_SECURE_NO_WARNINGS
-D_SCL_SECURE_NO_WARNINGS
)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------------------------
# define the stub for delayed load of uxtheme.dll
# ------------------------------------
set( uxtheme_stub_SOURCES
"${CMAKE_CURRENT_SOURCE_DIR}/uxtheme-stub/uxtheme-stub.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/uxtheme-stub/uxtheme-stub.def"
)
add_library(uxtheme-stub  SHARED ${uxtheme_stub_SOURCES} )
# ------------------------------------
# dark lib
# ------------------------------------
set( dark_lib_SOURCES
"${CMAKE_CURRENT_SOURCE_DIR}/DarkMode/IatHook.h"
"${CMAKE_CURRENT_SOURCE_DIR}/DarkMode/framework.h"
"${CMAKE_CURRENT_SOURCE_DIR}/DarkMode/targetver.h"
"${CMAKE_CURRENT_SOURCE_DIR}/DarkMode/UAHMenuBar.c"
"${CMAKE_CURRENT_SOURCE_DIR}/DarkMode/UAHMenuBar.h"
#"${CMAKE_CURRENT_SOURCE_DIR}/DarkMode/wrapper.h"
#"${CMAKE_CURRENT_SOURCE_DIR}/DarkMode/wrapper.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/DarkMode/dark_mode.h"
"${CMAKE_CURRENT_SOURCE_DIR}/DarkMode/dark_mode.cpp"
)
add_library(dark_lib  STATIC ${dark_lib_SOURCES} )
# -------------------------------------------
# Main
# -------------------------------------------
set( headers 
   "scintilla/include/GraphicUtils.h"
    "scintilla/include/ILexer.h"
    "scintilla/include/ILoader.h"
    "scintilla/include/LaTeXInput.h"
    "scintilla/include/Sci_Position.h"
    "scintilla/include/SciLexer.h"
    "scintilla/include/Scintilla.h"
    "scintilla/include/ScintillaMessages.h"
    "scintilla/include/ScintillaStructures.h"
    "scintilla/include/ScintillaTypes.h"
    "scintilla/include/VectorISA.h"
    "scintilla/lexlib/Accessor.h"
    "scintilla/lexlib/CharacterCategory.h"
    "scintilla/lexlib/CharacterSet.h"
    "scintilla/lexlib/DefaultLexer.h"
    "scintilla/lexlib/DocUtils.h"
    "scintilla/lexlib/LexAccessor.h"
    "scintilla/lexlib/LexerBase.h"
    "scintilla/lexlib/LexerModule.h"
    "scintilla/lexlib/LexerUtils.h"
    "scintilla/lexlib/OptionSet.h"
    "scintilla/lexlib/PropSetSimple.h"
    "scintilla/lexlib/SparseState.h"
    "scintilla/lexlib/StringUtils.h"
    "scintilla/lexlib/StyleContext.h"
    "scintilla/lexlib/SubStyles.h"
    "scintilla/lexlib/WordList.h"
    "scintilla/src/AutoComplete.h"
    "scintilla/src/CallTip.h"
    "scintilla/src/CaseConvert.h"
    "scintilla/src/CaseFolder.h"
    "scintilla/src/CellBuffer.h"
    "scintilla/src/ChangeHistory.h"
    "scintilla/src/CharClassify.h"
    "scintilla/src/ContractionState.h"
    "scintilla/src/Decoration.h"
    "scintilla/src/Document.h"
    "scintilla/src/EditModel.h"
    "scintilla/src/Editor.h"
    "scintilla/src/EditView.h"
    "scintilla/src/ElapsedPeriod.h"
    "scintilla/src/Geometry.h"
    "scintilla/src/Indicator.h"
    "scintilla/src/KeyMap.h"
    "scintilla/src/LineMarker.h"
    "scintilla/src/MarginView.h"
    "scintilla/src/ParallelSupport.h"
    "scintilla/src/Partitioning.h"
    "scintilla/src/PerLine.h"
    "scintilla/src/Platform.h"
    "scintilla/src/Position.h"
    "scintilla/src/PositionCache.h"
    "scintilla/src/RESearch.h"
    "scintilla/src/RunStyles.h"
    "scintilla/src/ScintillaBase.h"
    "scintilla/src/Selection.h"
    "scintilla/src/SparseVector.h"
    "scintilla/src/SplitVector.h"
    "scintilla/src/Style.h"
    "scintilla/src/UniConversion.h"
    "scintilla/src/UniqueString.h"
    "scintilla/src/ViewStyle.h"
    "scintilla/src/XPM.h"
    "scintilla/win32/HanjaDic.h"
    "scintilla/win32/PlatWin.h"
    "scintilla/win32/WinTypes.h"
    "src/compiler.h"
    "src/config.h"
    "src/Dialogs.h"
    "src/Dlapi.h"
    "src/Edit.h"
    "src/EditLexer.h"
    "src/EditLexers/EditStyle.h"
    "src/EditLexers/EditStyleX.h"
    "src/Helpers.h"
    "src/Notepad2.h"
    "src/Resource.h"
    "src/SciCall.h"
    "src/Styles.h"
    "src/Version.h"
    "src/VersionRev.h"
)

set( sources 
   "scintilla/lexers/LexAPDL.cxx"
    "scintilla/lexers/LexAsm.cxx"
    "scintilla/lexers/LexAsymptote.cxx"
    "scintilla/lexers/LexAutoHotkey.cxx"
    "scintilla/lexers/LexAutoIt3.cxx"
    "scintilla/lexers/LexAviSynth.cxx"
    "scintilla/lexers/LexAwk.cxx"
    "scintilla/lexers/LexBash.cxx"
    "scintilla/lexers/LexBatch.cxx"
    "scintilla/lexers/LexCIL.cxx"
    "scintilla/lexers/LexCMake.cxx"
    "scintilla/lexers/LexCoffeeScript.cxx"
    "scintilla/lexers/LexConfig.cxx"
    "scintilla/lexers/LexCPP.cxx"
    "scintilla/lexers/LexCSharp.cxx"
    "scintilla/lexers/LexCSS.cxx"
    "scintilla/lexers/LexCSV.cxx"
    "scintilla/lexers/LexD.cxx"
    "scintilla/lexers/LexDart.cxx"
    "scintilla/lexers/LexDiff.cxx"
    "scintilla/lexers/LexFortran.cxx"
    "scintilla/lexers/LexFSharp.cxx"
    "scintilla/lexers/LexGN.cxx"
    "scintilla/lexers/LexGo.cxx"
    "scintilla/lexers/LexGraphViz.cxx"
    "scintilla/lexers/LexGroovy.cxx"
    "scintilla/lexers/LexHaskell.cxx"
    "scintilla/lexers/LexHaxe.cxx"
    "scintilla/lexers/LexHTML.cxx"
    "scintilla/lexers/LexInno.cxx"
    "scintilla/lexers/LexJava.cxx"
    "scintilla/lexers/LexJam.cxx"
    "scintilla/lexers/LexJavaScript.cxx"
    "scintilla/lexers/LexJSON.cxx"
    "scintilla/lexers/LexJulia.cxx"
    "scintilla/lexers/LexKotlin.cxx"
    "scintilla/lexers/LexLaTeX.cxx"
    "scintilla/lexers/LexLisp.cxx"
    "scintilla/lexers/LexLLVM.cxx"
    "scintilla/lexers/LexLua.cxx"
    "scintilla/lexers/LexMakefile.cxx"
    "scintilla/lexers/LexMarkdown.cxx"
    "scintilla/lexers/LexMathematica.cxx"
    "scintilla/lexers/LexMatlab.cxx"
    "scintilla/lexers/LexNim.cxx"
    "scintilla/lexers/LexNSIS.cxx"
    "scintilla/lexers/LexNull.cxx"
    "scintilla/lexers/LexOCaml.cxx"
    "scintilla/lexers/LexPascal.cxx"
    "scintilla/lexers/LexPerl.cxx"
    "scintilla/lexers/LexPHP.cxx"
    "scintilla/lexers/LexPowerShell.cxx"
    "scintilla/lexers/LexProps.cxx"
    "scintilla/lexers/LexPython.cxx"
    "scintilla/lexers/LexR.cxx"
    "scintilla/lexers/LexRebol.cxx"
    "scintilla/lexers/LexRuby.cxx"
    "scintilla/lexers/LexRust.cxx"
    "scintilla/lexers/LexScala.cxx"
    "scintilla/lexers/LexSmali.cxx"
    "scintilla/lexers/LexSQL.cxx"
    "scintilla/lexers/LexSwift.cxx"
    "scintilla/lexers/LexTCL.cxx"
    "scintilla/lexers/LexTexinfo.cxx"
    "scintilla/lexers/LexTOML.cxx"
    "scintilla/lexers/LexVB.cxx"
    "scintilla/lexers/LexVerilog.cxx"
    "scintilla/lexers/LexVHDL.cxx"
    "scintilla/lexers/LexVim.cxx"
    "scintilla/lexers/LexWASM.cxx"
    "scintilla/lexers/LexWinHex.cxx"
    "scintilla/lexers/LexYAML.cxx"
    "scintilla/lexers/LexZig.cxx"
    "scintilla/lexlib/Accessor.cxx"
    "scintilla/lexlib/CharacterCategory.cxx"
    "scintilla/lexlib/DefaultLexer.cxx"
    "scintilla/lexlib/LexAccessor.cxx"
    "scintilla/lexlib/LexerBase.cxx"
    "scintilla/lexlib/LexerModule.cxx"
    "scintilla/lexlib/PropSetSimple.cxx"
    "scintilla/lexlib/StyleContext.cxx"
    "scintilla/lexlib/WordList.cxx"
    "scintilla/src/AutoComplete.cxx"
    "scintilla/src/CallTip.cxx"
    "scintilla/src/CaseConvert.cxx"
    "scintilla/src/CaseFolder.cxx"
    "scintilla/src/CellBuffer.cxx"
    "scintilla/src/ChangeHistory.cxx"
    "scintilla/src/CharClassify.cxx"
    "scintilla/src/ContractionState.cxx"
    "scintilla/src/Decoration.cxx"
    "scintilla/src/Document.cxx"
    "scintilla/src/EditModel.cxx"
    "scintilla/src/Editor.cxx"
    "scintilla/src/EditView.cxx"
    "scintilla/src/Geometry.cxx"
    "scintilla/src/Indicator.cxx"
    "scintilla/src/KeyMap.cxx"
    "scintilla/src/LineMarker.cxx"
    "scintilla/src/MarginView.cxx"
    "scintilla/src/PerLine.cxx"
    "scintilla/src/PositionCache.cxx"
    "scintilla/src/RESearch.cxx"
    "scintilla/src/RunStyles.cxx"
    "scintilla/src/ScintillaBase.cxx"
    "scintilla/src/Selection.cxx"
    "scintilla/src/Style.cxx"
    "scintilla/src/UniConversion.cxx"
    "scintilla/src/UniqueString.cxx"
    "scintilla/src/ViewStyle.cxx"
    "scintilla/src/XPM.cxx"
    "scintilla/win32/HanjaDic.cxx"
    "scintilla/win32/LaTeXInput.cxx"
    "scintilla/win32/PlatWin.cxx"
    "scintilla/win32/ScintillaWin.cxx"
    "src/Bridge.cpp"
    "src/Dialogs.c"
    "src/Dlapi.c"
    "src/Edit.c"
    "src/EditAutoC.c"
    "src/EditEncoding.c"
    "src/Helpers.c"
    "src/Notepad2.c"
    "src/Notepad2.rc"
    "src/Styles.c"
    "src/EditLexers/stlABAQUS.c"
    "src/EditLexers/stlActionScript.c"
    "src/EditLexers/stlAPDL.c"
    "src/EditLexers/stlAsm.c"
    "src/EditLexers/stlAsymptote.c"
    "src/EditLexers/stlAutoHotkey.c"
    "src/EditLexers/stlAutoIt3.c"
    "src/EditLexers/stlAviSynth.c"
    "src/EditLexers/stlAwk.c"
    "src/EditLexers/stlBash.c"
    "src/EditLexers/stlBatch.c"
    "src/EditLexers/stlBlockdiag.c"
    "src/EditLexers/stlCIL.c"
    "src/EditLexers/stlCMake.c"
    "src/EditLexers/stlCoffeeScript.c"
    "src/EditLexers/stlCPP.c"
    "src/EditLexers/stlCSharp.c"
    "src/EditLexers/stlCSS.c"
    "src/EditLexers/stlD.c"
    "src/EditLexers/stlDart.c"
    "src/EditLexers/stlDefault.c"
    "src/EditLexers/stlFortran.c"
    "src/EditLexers/stlFSharp.c"
    "src/EditLexers/stlGo.c"
    "src/EditLexers/stlGN.c"
    "src/EditLexers/stlGradle.c"
    "src/EditLexers/stlGraphViz.c"
    "src/EditLexers/stlGroovy.c"
    "src/EditLexers/stlHaskell.c"
    "src/EditLexers/stlHaxe.c"
    "src/EditLexers/stlHTML.c"
    "src/EditLexers/stlInno.c"
    "src/EditLexers/stlJamfile.c"
    "src/EditLexers/stlJava.c"
    "src/EditLexers/stlJavaScript.c"
    "src/EditLexers/stlJSON.c"
    "src/EditLexers/stlJulia.c"
    "src/EditLexers/stlKotlin.c"
    "src/EditLexers/stlLaTeX.c"
    "src/EditLexers/stlLisp.c"
    "src/EditLexers/stlLLVM.c"
    "src/EditLexers/stlLua.c"
    "src/EditLexers/stlMake.c"
    "src/EditLexers/stlMarkdown.c"
    "src/EditLexers/stlMathematica.c"
    "src/EditLexers/stlMATLAB.c"
    "src/EditLexers/stlNsis.c"
    "src/EditLexers/stlNim.c"
    "src/EditLexers/stlOCaml.c"
    "src/EditLexers/stlPascal.c"
    "src/EditLexers/stlPerl.c"
    "src/EditLexers/stlPHP.c"
    "src/EditLexers/stlPowerShell.c"
    "src/EditLexers/stlPython.c"
    "src/EditLexers/stlR.c"
    "src/EditLexers/stlRebol.c"
    "src/EditLexers/stlResource.c"
    "src/EditLexers/stlRuby.c"
    "src/EditLexers/stlRust.c"
    "src/EditLexers/stlScala.c"
    "src/EditLexers/stlSmali.c"
    "src/EditLexers/stlSQL.c"
    "src/EditLexers/stlSwift.c"
    "src/EditLexers/stlTcl.c"
    "src/EditLexers/stlTexinfo.c"
    "src/EditLexers/stlTOML.c"
    "src/EditLexers/stlTypeScript.c"
    "src/EditLexers/stlVB.c"
    "src/EditLexers/stlVBS.c"
    "src/EditLexers/stlVerilog.c"
    "src/EditLexers/stlVHDL.c"
    "src/EditLexers/stlVim.c"
    "src/EditLexers/stlWASM.c"
    "src/EditLexers/stlWinHex.c"
    "src/EditLexers/stlXML.c"
    "src/EditLexers/stlYAML.c"
    "src/EditLexers/stlZig.c"    
)

file(GLOB resources
     "res/*.*"
)
add_executable(${PROJECT_NAME} WIN32
${headers}
${sources}
${resources}
# src/editor.manifest
)
source_group("Source Files" FILES ${sources})
source_group("Header Files" FILES ${headers})
source_group("Resource Files" FILES ${resources})

include_directories("scintilla/lexlib")
include_directories("src/EditLexers")
include_directories("scintilla/src")
include_directories("src" "DarkMode")
include_directories("scintilla/win32")
include_directories("scintilla/include")
target_link_options(${PROJECT_NAME} PRIVATE  "/DELAYLOAD:uxtheme.dll")

target_link_libraries(${PROJECT_NAME}
comctl32
shlwapi
imm32
dwmapi
ntdll
OneCore
dark_lib
uxtheme-stub
# -manifest:embed -manifestinput:src/editor.manifest
)


set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

