#include "MobileMenuPage.h"

float fSpacing = 75.0f;
float fPosY0 = 0.0f;
float fPosY1 = -299.0f;
float fPosY2 = fPosY1 + fSpacing;
float fPosY3 = fPosY2 + fSpacing;
float fPosY4 = fPosY3 + fSpacing;
float fPosY5 = fPosY4 + fSpacing;
float fPosY6 = fPosY5 + fSpacing;
float fPosY7 = fPosY6 + fSpacing;
float fPosY8 = fPosY7 + fSpacing;
float fPosYd = fPosY7 + 112.0f;
float fPosYk = -188.0f;
float fPosYn = -188.0f;
float fPosYy = fPosYn + 50.0f;

void MobileMenuPage::InstallPatches() {
    plugin::patch::Set<void*>(0x57345A, &MenuPages->m_aButtons->m_nActionType);
    plugin::patch::Set<void*>(0x57370A, &MenuPages->m_nStartingButton);
    plugin::patch::Set<void*>(0x573713, &MenuPages->m_nPrevMenu);
    plugin::patch::Set<void*>(0x573728, &MenuPages->m_nPrevMenu);
    plugin::patch::Set<void*>(0x57373D, &MenuPages->m_nPrevMenu);
    plugin::patch::Set<void*>(0x573752, &MenuPages->m_nPrevMenu);
    plugin::patch::Set<void*>(0x573772, &MenuPages->m_aButtons->m_nTargetMenu);
    plugin::patch::Set<void*>(0x573EA9, &MenuPages->m_aButtons->m_nActionType);
    plugin::patch::Set<void*>(0x576B08, &MenuPages->m_aButtons[1].m_nTargetMenu);
    plugin::patch::Set<void*>(0x576B1E, &MenuPages->m_aButtons[1].m_nTargetMenu);
    plugin::patch::Set<void*>(0x576B38, &MenuPages);
    plugin::patch::Set<void*>(0x576B58, &MenuPages->m_aButtons->m_szName);
    plugin::patch::Set<void*>(0x57B4F2, &MenuPages->m_aButtons->m_nActionType);
    plugin::patch::Set<void*>(0x57B519, &MenuPages->m_aButtons->m_nActionType);
    plugin::patch::Set<void*>(0x57B52A, &MenuPages->m_aButtons->m_nActionType);
    plugin::patch::Set<void*>(0x57B534, &MenuPages->m_aButtons->m_nActionType);
    plugin::patch::Set<void*>(0x57B588, &MenuPages->m_aButtons->m_nActionType);
    plugin::patch::Set<void*>(0x57B5A4, &MenuPages->m_aButtons->m_nActionType);
    plugin::patch::Set<void*>(0x57B5C9, &MenuPages->m_aButtons->m_nActionType);
    plugin::patch::Set<void*>(0x57B5E9, &MenuPages->m_aButtons[1].m_nActionType);
    plugin::patch::Set<void*>(0x57B601, &MenuPages->m_aButtons->m_nActionType);
    plugin::patch::Set<void*>(0x57B629, &MenuPages->m_aButtons->m_nActionType);
    plugin::patch::Set<void*>(0x57B69C, &MenuPages->m_aButtons->m_nType);
    plugin::patch::Set<void*>(0x57B6F1, &MenuPages->m_aButtons->m_nType);
    plugin::patch::Set<void*>(0x57C313, &MenuPages->m_aButtons->m_nActionType);
    plugin::patch::Set<void*>(0x57D6D8, &MenuPages->m_aButtons->m_szName);
    plugin::patch::Set<void*>(0x57D701, &MenuPages->m_aButtons->m_szName);
    plugin::patch::Set<void*>(0x57E3F7, &MenuPages->m_aButtons->m_nActionType);
    plugin::patch::Set<void*>(0x57FE0A, &MenuPages->m_aButtons->m_nActionType);
    plugin::patch::Set<void*>(0x57FE25, &MenuPages->m_aButtons->m_szName);
    plugin::patch::Set<void*>(0x57FF5F, &MenuPages->m_aButtons->m_nActionType);
    plugin::patch::Set<void*>(0x57FFAE, &MenuPages->m_aButtons->m_nActionType);
    plugin::patch::Set<void*>(0x580316, &MenuPages->m_aButtons->m_nActionType);
    plugin::patch::Set<void*>(0x580496, &MenuPages->m_aButtons->m_nActionType);
    plugin::patch::Set<void*>(0x5804EB, &MenuPages->m_aButtons->m_nActionType);
    plugin::patch::Set<void*>(0x5805D3, &MenuPages->m_aButtons->m_nActionType);
    plugin::patch::Set<void*>(0x57FE57, &MenuPages->m_aButtons->m_nPosnX);
    plugin::patch::Set<void*>(0x57FE96, &MenuPages->m_aButtons->m_nPosnY);
    plugin::patch::Set<void*>(0x57B6AD, &FrontEndMobileMenuManager.SlotValidation);
    plugin::patch::Set<void*>(0x619157, &FrontEndMobileMenuManager.SlotValidation[1]);
    plugin::patch::Set<void*>(0x61922D, &FrontEndMobileMenuManager.SlotValidation[1]);
    plugin::patch::Set<void*>(0x619247, &FrontEndMobileMenuManager.SlotValidation[1]);
}

MyMenuPage MobileMenuPage::PagesMenu[] = {
    // Stats
    {   "FEH_STA", 42, 3,
    21, "FES_PLA",       MENU_ENTRY_OPTION,      0,  0,  fPosY1,  0,
    21, "FES_MON",       MENU_ENTRY_OPTION,      0,  0,  fPosY2,  0,
    21, "FES_WEA",       MENU_ENTRY_OPTION,      0,  0,  fPosY3,  0,
    21, "FES_CRI",       MENU_ENTRY_OPTION,      0,  0,  fPosY4,  0,
    21, "FES_GAN",       MENU_ENTRY_OPTION,      0,  0,  fPosY5,  0,
    21, "FES_ACH",       MENU_ENTRY_OPTION,      0,  0,  fPosY6,  0,
    21, "FES_MIS",       MENU_ENTRY_OPTION,      0,  0,  fPosY7,  0,
    21, "FES_MSC",       MENU_ENTRY_OPTION,      0,  0,  fPosY8,  0,
    },

    // Game
    {    "FEH_LOA", 42, 5,
    10,  "FES_NGA",      MENU_ENTRY_BUTTON,      6,  0,  fPosY1,  0,
     5,  "FES_LOA",      MENU_ENTRY_BUTTON,      9,  0,  fPosY2,  0,
     5,  "FES_DEL",      MENU_ENTRY_BUTTON,     10,  0,  fPosY3,  0,
    },

    // Brief
    {    "FEH_BRI", 42, 4,
    },

    // Audio Setup
    {    "FEH_AUD", 33, 3,
    28,  "FEA_MUS",      MENU_ENTRY_OPTION,       3,  0,  fPosY1,  0,
    29,  "FEA_SFX",      MENU_ENTRY_OPTION,       3,  0,  fPosY2,  0,
    30,  "FEA_BAS",      MENU_ENTRY_OPTION,       3,  0,  fPosY3,  0,
    31,  "FEA_ART",      MENU_ENTRY_OPTION,       3,  0,  fPosY4,  0,
     5,  "FEA_TIT",      MENU_ENTRY_BUTTON,      26,  0,  fPosY5,  0,
    32,  "FEA_RSS",      MENU_ENTRY_OPTION,       3,  0,  fPosY6,  0,
     5,  "FET_DEF",      MENU_ENTRY_BUTTON,      24,  0,  fPosYd,  0,
    },

    // Display Setup
    {    "FEH_DIS", 33, 2,
    27,  "FED_BRI",     MENU_ENTRY_OPTION,        4,  0,  fPosY1,  0,
    42,  "FED_FXQ",     MENU_ENTRY_OPTION,       27,  0,  fPosY2,  0,
    56,  "FED_RES",     MENU_ENTRY_OPTION,       27,  0,  fPosY3,  0,
    61,  "FEM_LOD",     MENU_ENTRY_OPTION,       27,  0,  fPosY4,  0,
    26,  "FED_WIS",     MENU_ENTRY_OPTION,       27,  0,  fPosY5,  0,
    44,  "FED_AAS",     MENU_ENTRY_OPTION,       27,  0,  fPosY6,  0,
    25,  "FED_SUB",     MENU_ENTRY_OPTION,        4,  0,  fPosY7,  0,
     5,  "FET_DEF",     MENU_ENTRY_BUTTON,       23,  0,  fPosYd,  0,
    },

    // Map
    {    "BLANK", 42, 1,
    },

    // New Game
    {    "FES_NGA", 1, 0,
     1,  "FESZ_QR",     MENU_ACTION_TEXT,         0,  0,  fPosY0,  0,
     4,  "FEM_NO",      MENU_ENTRY_BUTTON,        1,  0,  fPosYn,  0,
    14,  "FEM_YES",     MENU_ENTRY_BUTTON,        6,  0,  fPosYy,  0,
    },

    // MPACK
    {    "FES_NGA", 1, 0,
     1,  "FEN_NGS",     MENU_ACTION_TEXT,         0,  0,  fPosY1,  0,
     5,  "FEN_NGX",     MENU_ENTRY_BUTTON,        6,  0,  fPosY2,  0,
    },

    // MPACK Load Mission
    {    "FES_LMI", 1, 0,
     1,  "FESZ_QM",     MENU_ACTION_TEXT,         0,  0,  fPosY0,  0,
     4,  "FEM_NO",      MENU_ENTRY_BUTTON,        1,  0,  fPosY1,  0,
    12,  "FEM_YES",     MENU_ENTRY_BUTTON,        0,  0,  fPosY2,  0,
    },

    // Load Game
    {    "FET_LG", 1, 1,
     1,  "BLANK",       MENU_ACTION_TEXT,         0,  0,  fPosY0,  0,
    13,  "FEM_SL1",     MENU_ENTRY_SAVE_1,        0,  0,  fPosY1,  0,
    13,  "FEM_SL2",     MENU_ENTRY_SAVE_2,        0,  0,  fPosY2,  0,
    13,  "FEM_SL3",     MENU_ENTRY_SAVE_3,        0,  0,  fPosY3,  0,
    13,  "FEM_SL4",     MENU_ENTRY_SAVE_4,        0,  0,  fPosY4,  0,
    13,  "FEM_SL5",     MENU_ENTRY_SAVE_5,        0,  0,  fPosY5,  0,
    13,  "FEM_SL6",     MENU_ENTRY_SAVE_6,        0,  0,  fPosY6,  0,
    13,  "FEM_SL7",     MENU_ENTRY_SAVE_7,        0,  0,  fPosY7,  0,
    13,  "FEM_SL8",     MENU_ENTRY_SAVE_8,        0,  0,  fPosY8,  0,
    },

    // Delete Game
    {    "FES_DEL", 1, 2,
    1,   "BLANK",       MENU_ACTION_TEXT,         0,  0,  fPosY0,  0,
    13,  "FEM_SL1",     MENU_ENTRY_SAVE_1,        0,  0,  fPosY1,  0,
    13,  "FEM_SL2",     MENU_ENTRY_SAVE_2,        0,  0,  fPosY2,  0,
    13,  "FEM_SL3",     MENU_ENTRY_SAVE_3,        0,  0,  fPosY3,  0,
    13,  "FEM_SL4",     MENU_ENTRY_SAVE_4,        0,  0,  fPosY4,  0,
    13,  "FEM_SL5",     MENU_ENTRY_SAVE_5,        0,  0,  fPosY5,  0,
    13,  "FEM_SL6",     MENU_ENTRY_SAVE_6,        0,  0,  fPosY6,  0,
    13,  "FEM_SL7",     MENU_ENTRY_SAVE_7,        0,  0,  fPosY7,  0,
    13,  "FEM_SL8",     MENU_ENTRY_SAVE_8,        0,  0,  fPosY8,  0,
    },

    // Load Game Action
    {    "FET_LG", 9, 0,
     1,  "FESZ_QL",     MENU_ACTION_TEXT,         0,  0,  fPosY0,  0,
     4,  "FEM_NO",      MENU_ENTRY_BUTTON,        9,  0,  fPosYn,  0,
     3,  "FEM_YES",     MENU_ENTRY_BUTTON,       13,  0,  fPosYy,  0,
    },

    // Delete Game Action
    {    "FES_DEL", 10, 0,
     1,  "FESZ_QD",     MENU_ACTION_TEXT,         0,  0,  fPosY0,  0,
     4,  "FEM_NO",      MENU_ENTRY_BUTTON,       10,  0,  fPosYn,  0,
     3,  "FEM_YES",     MENU_ENTRY_BUTTON,       14,  0,  fPosYy,  0,
    },

    {    "FET_LG", 9, 0,
    },

    {    "FEH_DEL", 10, 0,
    },

    // Deleted Game Action
    {    "FES_DEL", 1, 0,
     1,  "FES_DSC",     MENU_ACTION_TEXT,         0,  0,  fPosY0,  0,
     5,  "FEM_OK",      MENU_ENTRY_BUTTON,        1,  0,  fPosYk,  0,
    },

    // Save Game
    {    "FET_SG", 255, 0,
     1,  "BLANK",       MENU_ACTION_TEXT,         0,  0,  fPosY0,  0,
    18,  "FEM_SL1",     MENU_ENTRY_SAVE_1,        0,  0,  fPosY1,  0,
    18,  "FEM_SL2",     MENU_ENTRY_SAVE_2,        0,  0,  fPosY2,  0,
    18,  "FEM_SL3",     MENU_ENTRY_SAVE_3,        0,  0,  fPosY3,  0,
    18,  "FEM_SL4",     MENU_ENTRY_SAVE_4,        0,  0,  fPosY4,  0,
    18,  "FEM_SL5",     MENU_ENTRY_SAVE_5,        0,  0,  fPosY5,  0,
    18,  "FEM_SL6",     MENU_ENTRY_SAVE_6,        0,  0,  fPosY6,  0,
    18,  "FEM_SL7",     MENU_ENTRY_SAVE_7,        0,  0,  fPosY7,  0,
    18,  "FEM_SL8",     MENU_ENTRY_SAVE_8,        0,  0,  fPosY8,  0,
    },
    
    // Save Game Action
    {    "FET_SG", 16, 0,
     1,  "FESZ_QZ",     MENU_ACTION_TEXT,         0,  0,  fPosY0,  0,
     4,  "FEM_NO",      MENU_ENTRY_BUTTON,       16,  0,  fPosYn,  0,
     3,  "FEM_YES",     MENU_ENTRY_BUTTON,       18,  0,  fPosYy,  0,
    },

    {    "FET_SG", 16, 0,
    },

    // Saved Game Action
    {    "FET_SG", 16, 0,
     1,  "FES_SSC",     MENU_ACTION_TEXT,         0,  0,  fPosY0,  0,
    54,  "FEM_OK",      MENU_ENTRY_BUTTON,        0,  0,  fPosYk,  0,
    },

    {    "FET_SG", 42, 0,
     1,  "BLANK",       MENU_ACTION_TEXT,         0,  0,  fPosY0,  0,
     5,  "FEM_OK",      MENU_ENTRY_BUTTON,        0,  0,  fPosYk,  0,
    },

    {    "FET_LG", 42, 0,
     1,  "BLANK",       MENU_ACTION_TEXT,         0,  0,  fPosY0,  0,
     5,  "FEM_OK",      MENU_ENTRY_BUTTON,        0,  0,  fPosYk,  0,
    },

    {    "FET_SG", 1, 0,
     1,  "BLANK",       MENU_ACTION_TEXT,         0,  0,  fPosY0,  0,
     5,  "FEM_OK",      MENU_ENTRY_BUTTON,       16,  0,  fPosYk,  0,
    },
     
     // Display Setup - Restore default
    {     "FEH_DIS", 4, 6,
     1,   "FED_RDP",    MENU_ACTION_TEXT,         0,  0,  fPosY0,  0,
     5,   "FEM_NO",     MENU_ENTRY_BUTTON,        4,  0,  fPosYn,  0,
    57,   "FEM_YES",    MENU_ENTRY_BUTTON,        4,  0,  fPosYy,  0,
    },

     // Audio Setup - Restore default
    {     "FEH_AUD", 3, 5,
     1,   "FED_RDP",    MENU_ACTION_TEXT,         0,  0,  fPosY0,  0,
     5,   "FEM_NO",     MENU_ENTRY_BUTTON,        3,  0,  fPosYn,  0,
    57,   "FEM_YES",    MENU_ENTRY_BUTTON,        3,  0,  fPosYy,  0,
    },

    // Controller Setup - Restore default
    {     "FET_CTL", 36, 3,
     1,   "FED_RDP",    MENU_ACTION_TEXT,         0,  0,  fPosY0,  0,
     5,   "FEM_NO",     MENU_ENTRY_BUTTON,       36,  0,  fPosYn,  0,
    57,   "FEM_YES",    MENU_ENTRY_BUTTON,       36,  0,  fPosYy,  0,
    },

    // Custom Tracks Options
    {     "FEA_TIT", 3, 3,
     1,   "FEA_SUB",    MENU_ACTION_TEXT,         0,  0,  fPosY0,  0,
    63,   "FEA_MPM",    MENU_ENTRY_OPTION,       26,  0,  fPosY2,  0,
    64,   "FEA_AMS",    MENU_ENTRY_OPTION,       26,  0,  fPosY3,  0,
     6,   "FEA_SCN",    MENU_ENTRY_BUTTON,       26,  0,  fPosY4,  0,
    },

    {     "BLANK", 0, 0,
    },

    // Language Setup
    {     "FEH_LAN", 33, 4,
    37,   "FEL_ENG",    MENU_ENTRY_BUTTON,       28,  0,  fPosY1,  0,
    38,   "FEL_FRE",    MENU_ENTRY_BUTTON,       28,  0,  fPosY2,  0,
    39,   "FEL_GER",    MENU_ENTRY_BUTTON,       28,  0,  fPosY3,  0,
    40,   "FEL_ITA",    MENU_ENTRY_BUTTON,       28,  0,  fPosY4,  0,
    41,   "FEL_SPA",    MENU_ENTRY_BUTTON,       28,  0,  fPosY5,  0,
    },

    {     "FET_SG", 1, 0,
     1,   "FED_LWR",    MENU_ACTION_TEXT,         0,  0,  fPosY0,  0,
     5,   "FEC_OKK",    MENU_ENTRY_BUTTON,       16,  0,  fPosYk,  0,
    },


    {     "FET_SG", 16, 0,
     1,   "FEC_SVU",    MENU_ACTION_TEXT,         0,  0,  fPosY0,  0,
     5,   "FEC_OKK",    MENU_ENTRY_BUTTON,       16,  0,  fPosYk,  0,
    },


    {     "FET_LG", 16, 0,
     1,   "FEC_SVU",    MENU_ACTION_TEXT,         0,  0,  fPosY0,  0,
    },


    {     "FET_LG", 1, 0,
     1,   "FEC_LUN",    MENU_ACTION_TEXT,         0,  0,  fPosY0,  0,
     2,   "FEDS_TB",    MENU_ACTION_BACK,         1,  0,  fPosYk,  0,
    },

    // Options
    {     "FET_OPT", 42, 2,
     5,   "FEO_CON",    MENU_ENTRY_BUTTON,       36,  0,  fPosY1,  0,
     5,   "FEH_LOA",    MENU_ENTRY_BUTTON,       44,  0,  fPosY2,  0,
     5,   "FEO_DIS",    MENU_ENTRY_BUTTON,        4,  0,  fPosY3,  0,
     5,   "FEO_AUD",    MENU_ENTRY_BUTTON,        3,  0,  fPosY4,  0,
     5,   "FEO_LAN",    MENU_ENTRY_BUTTON,       28,  0,  fPosY5,  0,
    },

    // Main Menu 
    {     "FEM_MM", 255, 0,
     5,   "FEP_STG",    MENU_ENTRY_BUTTON,        1,  0,  fPosY1,  0,
     5,   "FEP_OPT",    MENU_ENTRY_BUTTON,       33,  0,  fPosY2,  0,
     5,   "FEP_QUI",    MENU_ENTRY_BUTTON,       35,  0,  fPosY3,  0,
    },

    // Quit
    {     "FET_QG", 42, 6,
     1,   "FEQ_SRE",    MENU_ACTION_TEXT,         0,  0,  fPosY0,  0,
    55,   "FEM_NO",     MENU_ENTRY_BUTTON,       42,  0,  fPosYn,  0,
    53,   "FEM_YES",    MENU_ENTRY_BUTTON,       42,  0,  fPosYy,  0,
    },

    // Controller Setup
    {     "FET_CTL", 33, 0,
    58,   "FEC_CFG",    MENU_ENTRY_OPTION,       36,  0,  fPosY1,  0,
     5,   "FEC_RED",    MENU_ENTRY_BUTTON,       37,  0,  fPosY2,  0,
     7,   "FEC_CFG",    MENU_ENTRY_JOYMOUSE,     36,  0,  fPosY3,  0,
     5,   "FET_DEF",    MENU_ENTRY_BUTTON,       25,  0,  fPosYd,  0,
    },

    // Controller Setup - Redefine Control
    {     "FET_CTL", 36, 1,
     8,   "FET_CFT",    MENU_ENTRY_BUTTON,       38,  0,  fPosY1,  0,
     9,   "FET_CCR",    MENU_ENTRY_BUTTON,       38,  0,  fPosY2,  0,
    },

    {     "FET_CTL", 37, 0,
    },

    // Controller Setup - Mouse Settings
    {     "FEC_MOU", 36, 2,
    62,   "FEC_MSH",    MENU_ENTRY_OPTION,       39,  0,  fPosY1,  0,
    46,   "FEC_IVV",    MENU_ENTRY_OPTION,       39,  0,  fPosY2,  0,
    59,   "FET_MST",    MENU_ENTRY_OPTION,       39,  0,  fPosY3,  0,
    60,   "FET_MFL",    MENU_ENTRY_OPTION,       39,  0,  fPosY4,  0,
    },

    {     "FET_CTL", 36, 2,
    47,   "FEJ_INX",    MENU_ENTRY_OPTION,       40,  0,  fPosY1,  2,
    48,   "FEJ_INY",    MENU_ENTRY_OPTION,       40,  0,  fPosY2,  2,
    51,   "FEJ_INA",    MENU_ENTRY_OPTION,       40,  0,  fPosY3,  2,
    49,   "FEJ_RNX",    MENU_ENTRY_OPTION,       40,  0,  fPosY4,  2,
    50,   "FEJ_RNY",    MENU_ENTRY_OPTION,       40,  0,  fPosY5,  2,
    52,   "FEJ_RNA",    MENU_ENTRY_OPTION,       40,  0,  fPosY6,  2, 
    },

    // Pause Menu
    {     "FET_PAU", 255, 0,
    54,   "FEP_RES",    MENU_ENTRY_BUTTON,        0,  0,  fPosY1,  0,
     5,   "FEH_MAP",    MENU_ENTRY_BUTTON,        5,  0,  fPosY2,  0,
     5,   "FEP_OPT",    MENU_ENTRY_BUTTON,       33,  0,  fPosY3,  0,
     5,   "FEP_STA",    MENU_ENTRY_BUTTON,        0,  0,  fPosY4,  0,
     5,   "FEP_BRI",    MENU_ENTRY_BUTTON,        2,  0,  fPosY5,  0,
     5,   "FEP_STG",    MENU_ENTRY_BUTTON,        1,  0,  fPosY6,  0,
     5,   "FEP_QUI",    MENU_ENTRY_BUTTON,       35,  0,  fPosY7,  0,
    },

    {     "", 0, 0,
    },

    {     "", 0, 0,
    },

    // Game Settings
    {     "FEH_LOA", 33, 1,
    35,   "FED_HUD",    MENU_ENTRY_OPTION,       4,  0,  fPosY1,  0,
    24,   "FEM_FRM",    MENU_ENTRY_OPTION,      27,  0,  fPosY2,  0,
    65,   "FED_GLS",    MENU_ENTRY_OPTION,       4,  0,  fPosY3,  0,
   100,   "FEN_NET",    MENU_ENTRY_BUTTON,       0,  0,  fPosY4,  0,
    }
};