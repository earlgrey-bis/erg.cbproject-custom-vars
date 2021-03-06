/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 */

#ifndef COMPILEROPTIONSDLG_H
#define COMPILEROPTIONSDLG_H

#include <vector>
#include <wx/intl.h>
#include <wx/string.h>
#include "configurationpanel.h"
#include "compileroptions.h"

class wxListBox;
class ScopeTreeData;
class cbProject;
class ProjectBuildTarget;
class CompilerGCC;
class wxSpinEvent;
class wxTreeEvent;
class wxCommandEvent;
class wxKeyEvent;
class wxPropertyGrid;
class wxPropertyGridEvent;
class wxUpdateUIEvent;
//  ................................................................................................    ERG+
class wxDataViewListCtrl;
class wxDataViewListStore;
class wxDataViewEvent;
//  ................................................................................................    ERG-

class CompilerOptionsDlg : public cbConfigurationPanel
{
    public:
        CompilerOptionsDlg(wxWindow* parent, CompilerGCC* compiler, cbProject* project = 0L, ProjectBuildTarget* target = 0L);
        ~CompilerOptionsDlg();

        virtual wxString GetTitle() const { return _("Global compiler settings"); }
        virtual wxString GetBitmapBaseName() const { return _T("compiler"); }
        virtual void OnApply();
        virtual void OnCancel(){}
    private:
        void TextToOptions();
        void OptionsToText();
        void DoFillCompilerSets(int compilerIdx);
        void DoFillCompilerPrograms();
        //  ........................................................................................    ERG+
        void WxModelAddVarHelper(bool _i_active, wxString const& _i_key, wxString const& _i_val, wxString const& _i_com = wxString(""));
        //  ........................................................................................    ERG-
        void DoFillVars();
        void DoFillOthers();
        void DoFillOptions();
        void DoFillCompilerDependentSettings();
        void DoSaveCompilerDependentSettings();
        void DoFillTree();
        void DoSaveOptions();
        void DoLoadOptions();
        void DoSaveCompilerPrograms();
        void DoSaveVars();
        void DoSaveCompilerDefinition();
        void CompilerChanged();
        void UpdateCompilerForTargets(int compilerIdx);
        void AutoDetectCompiler();
        wxListBox* GetDirsListBox();
        CompileOptionsBase* GetVarsOwner();
        void ProjectTargetCompilerAdjust(); //!< checks if compiler changed for project/target and takes actions accordingly

        void OnRealApply(); // user clicked the "Apply" button (so not the Ok button !!!)
        void OnTreeSelectionChange(wxTreeEvent& event);
        void OnTreeSelectionChanging(wxTreeEvent& event);
        void OnCompilerChanged(wxCommandEvent& event);
        void OnCategoryChanged(wxCommandEvent& event);
        void OnOptionChanged(wxPropertyGridEvent& event);
        void OnAddDirClick(wxCommandEvent& event);
        void OnEditDirClick(wxCommandEvent& event);
        void OnRemoveDirClick(wxCommandEvent& event);
        void OnClearDirClick(wxCommandEvent& event);
        void OnCopyDirsClick(wxCommandEvent& event);
        void OnAddVarClick(wxCommandEvent& event);
        //  ........................................................................................    ERG+
        void OnBrowseVarClick(wxCommandEvent& event);
        void WxModelSaveComment(int _i_row);
        void WxModelShowComment(int _i_row);
        void OnVarListVarChanged(wxDataViewEvent&);                                                 //!< a variable was edited from within the wxDataViewListCtrl
        void OnVarListSelChanged(wxDataViewEvent&);                                                 //!< another variable was selected
        void OnTextEvent(wxCommandEvent&);                                                          //!<
        //  ........................................................................................    ERG-
        void OnRemoveVarClick(wxCommandEvent& event);
        void OnDeleteAllVarsClick(wxCommandEvent& event);
        void OnSetDefaultCompilerClick(wxCommandEvent& event);
        void OnAddCompilerClick(wxCommandEvent& event);
        void OnEditCompilerClick(wxCommandEvent& event);
        void OnRemoveCompilerClick(wxCommandEvent& event);
        void OnResetCompilerClick(wxCommandEvent& event);
        void OnAddLibClick(wxCommandEvent& event);
        void OnEditLibClick(wxCommandEvent& event);
        void OnRemoveLibClick(wxCommandEvent& event);
        void OnClearLibClick(wxCommandEvent& event);
        void OnCopyLibsClick(wxCommandEvent& event);
        void OnMoveLibUpClick(wxCommandEvent& event);
        void OnMoveLibDownClick(wxCommandEvent& event);
        void OnMoveDirUpClick(wxCommandEvent& event);
        void OnMoveDirDownClick(wxCommandEvent& event);
        void OnMasterPathClick(wxCommandEvent& event);
        void OnAutoDetectClick(wxCommandEvent& event);
        void OnSelectProgramClick(wxCommandEvent& event);
        void OnAdvancedClick(wxCommandEvent& event);
        void OnAddExtraPathClick(wxCommandEvent& event);
        void OnEditExtraPathClick(wxCommandEvent& event);
        void OnRemoveExtraPathClick(wxCommandEvent& event);
        void OnClearExtraPathClick(wxCommandEvent& event);
        void OnIgnoreAddClick(wxCommandEvent& event);
        void OnIgnoreRemoveClick(wxCommandEvent& event);
        void OnUpdateUI(wxUpdateUIEvent& event);
        void OnDirty(wxCommandEvent& event); // some controls who change their value -> dirty
        void OnMyCharHook(wxKeyEvent& event);
        void OnFlagsPopup(wxPropertyGridEvent& event);
        void OnFlagsPopupClick(wxCommandEvent& event);
        void OnOptionDoubleClick(wxPropertyGridEvent& event);

    private:
        wxPropertyGrid*              m_FlagsPG;
        CompilerGCC*                 m_Compiler;
        CompilerOptions              m_Options;
        wxArrayString                m_LinkerOptions;
        wxArrayString                m_LinkLibs;
        wxArrayString                m_CompilerOptions;
        wxArrayString                m_ResourceCompilerOptions;
        //  ........................................................................................    ERG+
        wxDataViewListCtrl      *   m_VarsWxCtrl;
        wxDataViewListStore     *   m_VarsWxModel;
        int                         m_VarsPrevSelModRow;            //!< model's row that was selected before the currently selected model's row
        //  ........................................................................................    ERG-
        int                          m_CurrentCompilerIdx;
        cbProject*                   m_pProject;
        ProjectBuildTarget*          m_pTarget;
        bool                         m_bDirty;                       //!< true if a setting has changed since last save
        bool                         m_bFlagsDirty;                  //!< true if a flag (not its value) has changed since last save
        wxString                     m_NewProjectOrTargetCompilerId; //!< keeps track of the changes of compiler of the selected project/target

        bool                         m_BuildingTree;                 //!< flag to ignore tree changing events while building it
        static int                   m_MenuOption;

        DECLARE_EVENT_TABLE()
};

#endif // COMPILEROPTIONSDLG_H
