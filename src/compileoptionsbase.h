/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef COMPILEOPTIONSBASE_H
#define COMPILEOPTIONSBASE_H

#include "globals.h"
#include <wx/hashmap.h>

WX_DECLARE_STRING_HASH_MAP(wxString, StringHash);

typedef struct
{
    wxString    value;
    wxString    comment;
    int         flags;
} CustomVar;

WX_DECLARE_STRING_HASH_MAP(CustomVar, CustomVarHash);

/// Enum which specifies which executable from the toolchain executables would be used for linking
/// the target.
enum class LinkerExecutableOption : int32_t
{
    /// For C-only projects this is the same as CCompiler, for C++ or mixed projects this is the
    /// same as CppCompiler.
    AutoDetect = 0,
    /// Use the C compiler executable.
    CCompiler,
    /// Use the C++ compiler executable.
    CppCompiler,
    /// Use the linker executable.
    Linker,

    /// Not valid options, used for range checks.
    Last,
    First = AutoDetect
};

/**
  * This is a base class for all classes needing compilation parameters. It
  * offers functions to get/set the following:\n
  * \li Compiler options
  * \li Linker options
  * \li Compiler include dirs
  * \li Resource compiler include dirs
  * \li Linker include dirs
  * \li Custom commands to be executed before/after build
  * \li The settings modification status
  * \n\n
  * These settings are used by the compiler plugins to construct the necessary
  * compilation commands.
  */
class DLLIMPORT CompileOptionsBase
{
    public:
        CompileOptionsBase();
        virtual ~CompileOptionsBase();

        virtual void AddPlatform(int platform);
        virtual void RemovePlatform(int platform);
        virtual void SetPlatforms(int platforms);
        virtual int GetPlatforms() const;
        virtual bool SupportsCurrentPlatform() const;

        virtual void SetLinkerOptions(const wxArrayString& linkerOpts);
        virtual const wxArrayString& GetLinkerOptions() const;
        virtual void AddLinkerOption(const wxString& option);
        virtual void ReplaceLinkerOption(const wxString& option, const wxString& new_option);
        virtual void RemoveLinkerOption(const wxString& option);

        virtual void SetLinkLibs(const wxArrayString& linkLibs);
        virtual const wxArrayString& GetLinkLibs() const;
        virtual void AddLinkLib(const wxString& option);
        virtual void ReplaceLinkLib(const wxString& option, const wxString& new_option);
        virtual void RemoveLinkLib(const wxString& option);

        virtual void SetLinkerExecutable(LinkerExecutableOption option);
        virtual LinkerExecutableOption GetLinkerExecutable() const;

        virtual void SetCompilerOptions(const wxArrayString& compilerOpts);
        virtual const wxArrayString& GetCompilerOptions() const;
        virtual void AddCompilerOption(const wxString& option);
        virtual void ReplaceCompilerOption(const wxString& option, const wxString& new_option);
        virtual void RemoveCompilerOption(const wxString& option);

        virtual void SetResourceCompilerOptions(const wxArrayString& resourceCompilerOpts);
        virtual const wxArrayString& GetResourceCompilerOptions() const;
        virtual void AddResourceCompilerOption(const wxString& option);
        virtual void ReplaceResourceCompilerOption(const wxString& option, const wxString& new_option);
        virtual void RemoveResourceCompilerOption(const wxString& option);

        virtual void SetIncludeDirs(const wxArrayString& includeDirs);
        virtual const wxArrayString& GetIncludeDirs() const;
        virtual void AddIncludeDir(const wxString& option);
        virtual void ReplaceIncludeDir(const wxString& option, const wxString& new_option);
        virtual void RemoveIncludeDir(const wxString& option);

        virtual void SetResourceIncludeDirs(const wxArrayString& resIncludeDirs);
        virtual const wxArrayString& GetResourceIncludeDirs() const;
        virtual void AddResourceIncludeDir(const wxString& option);
        virtual void ReplaceResourceIncludeDir(const wxString& option, const wxString& new_option);
        virtual void RemoveResourceIncludeDir(const wxString& option);

        virtual void SetLibDirs(const wxArrayString& libDirs);
        virtual const wxArrayString& GetLibDirs() const;
        virtual void AddLibDir(const wxString& option);
        virtual void ReplaceLibDir(const wxString& option, const wxString& new_option);
        virtual void RemoveLibDir(const wxString& option);

        virtual void SetCommandsBeforeBuild(const wxArrayString& commands);
        virtual const wxArrayString& GetCommandsBeforeBuild() const;
        virtual void AddCommandsBeforeBuild(const wxString& command);
        virtual void RemoveCommandsBeforeBuild(const wxString& command);

        virtual void SetCommandsAfterBuild(const wxArrayString& commands);
        virtual const wxArrayString& GetCommandsAfterBuild() const;
        virtual void AddCommandsAfterBuild(const wxString& command);
        virtual void RemoveCommandsAfterBuild(const wxString& command);

        virtual void SetBuildScripts(const wxArrayString& scripts);
        virtual const wxArrayString& GetBuildScripts() const;
        virtual void AddBuildScript(const wxString& script);
        virtual void RemoveBuildScript(const wxString& script);

        virtual bool GetModified() const;
        virtual void SetModified(bool modified);

        virtual bool GetAlwaysRunPostBuildSteps() const;
        virtual void SetAlwaysRunPostBuildSteps(bool always);

        //  ........................................................................................    ERG+
        //  old var API ( assumes the variable is active ) :
        virtual bool SetVar(const wxString& key, const wxString& value, bool onlyIfExists = false); //!< old API, works only on active variables
        virtual bool UnsetVar(const wxString& key);                                                 //!< old API, works only on active variables
        virtual void UnsetAllVars();                                                                //!< old API, works only on active variables
        virtual bool HasVar(const wxString& key) const;                                             //!< old API, works only on active variables
        virtual const wxString& GetVar(const wxString& key) const;                                  //!< old API, works only on active variables

        //  new var API :
    public:
        enum
        {
            eVarActive      =   0x0001  ,                                                           //!< select active vars in API calls
            eVarInactive    =   0x0002  ,                                                           //!< select inactive vars in API calls

            eVarAll         =   0xffff                                                              //!< select all vars in API calls
        };

    public:
        virtual bool VarSet       (wxString const & _i_key, wxString const & _i_val, wxString const & _i_comment, int _i_flags, bool _i_only_if_exists = false);
        virtual bool VarSetValue  (wxString const & _i_key, wxString const & _i_val);
        virtual bool VarSetComment(wxString const & _i_key, wxString const & _i_com);
        virtual bool VarSetFlags  (wxString const & _i_key, int   _i_flags);
    private:
                bool VarGetIterator(wxString const & _i_key, CustomVarHash::iterator & _o_it);

    public:
        virtual bool VarHas       (wxString const & _i_key) const;
        virtual bool VarGet       (wxString const & _i_key, CustomVar & _o_cv) const;
        virtual bool VarGetValue  (wxString const & _i_key, wxString       & _o_val) const;
        virtual bool VarGetComment(wxString const & _i_key, wxString       & _o_com) const;
        virtual bool VarGetFlags  (wxString const & _i_key, int & _o_flags) const;

        virtual bool VarUnset(wxString const & _i_key);
        virtual void VarUnsetAll(int _i_activity_flags = (eVarActive & eVarInactive));

    private:
                CustomVarHash::const_iterator * VarEnumFind() const;
    public:
                CustomVarHash::const_iterator * VarEnumGetFirst(int _i_flags = eVarActive) const;
                CustomVarHash::const_iterator * VarEnumGetNext() const;
        //  ........................................................................................    ERG-
    protected:
        int m_Platform;
        LinkerExecutableOption m_LinkerExecutable;
        wxArrayString m_LinkerOptions;
        wxArrayString m_LinkLibs;
        wxArrayString m_CompilerOptions;
        wxArrayString m_ResourceCompilerOptions;
        wxArrayString m_IncludeDirs;
        wxArrayString m_ResIncludeDirs;
        wxArrayString m_LibDirs;
        wxArrayString m_CmdsBefore;
        wxArrayString m_CmdsAfter;
        wxArrayString m_Scripts;
        bool m_Modified;
        bool m_AlwaysRunPostCmds;
        //  ........................................................................................    ERG+
        CustomVarHash   m_Vars;                                                                     //!< map for CustomVars
        //  ........................................................................................    ERG+
    private:

};

#endif // COMPILEOPTIONSBASE_H

