#pragma once

#include "..//inode.h"

class CXI_IMAGE;

// edit box
class CXI_PCEDITBOX : public CINODE
{
  public:
    CXI_PCEDITBOX(CXI_PCEDITBOX &&) = delete;
    CXI_PCEDITBOX(const CXI_PCEDITBOX &) = delete;
    CXI_PCEDITBOX();
    ~CXI_PCEDITBOX();

    void ReleaseAll() override;
    void Draw(bool bSelected, uint32_t Delta_Time) override;
    bool Init(INIFILE *ini1, const char *name1, INIFILE *ini2, const char *name2, VDX9RENDER *rs, XYRECT &hostRect,
              XYPOINT &ScreenSize) override;
    int CommandExecute(int wActCode) override;
    bool IsClick(int buttonID, long xPos, long yPos) override;

    void MouseThis(float fX, float fY) override{};
    void ChangePosition(XYRECT &rNewPos) override;
    void SaveParametersToIni() override;

  protected:
    void LoadIni(INIFILE *ini1, const char *name1, INIFILE *ini2, const char *name2) override;
    void UpdateString(std::string &str);
    char GetInputSymbol();
    bool IsEditMode()
    {
        return IsCurrentNode();
    }
    void ShowCursorPosition(std::string &str);
    void InsertSymbol(std::string &str, utf8::u8_char chr);
    void DisguiseString(std::string &str);
    bool IsExcludeChar(utf8::u8_char chr) const;

  protected:
    long m_nFontID;          // font id
    uint32_t m_dwFontColor;  // color for font
    XYPOINT m_pntFontOffset; // string offset
    long m_nStringAlign;     // string alignment
    float m_fFontScale;      // font scale

    long m_nEditPos;  // position of current edited character
    long m_nMaxSize;  // max character quantity
    long m_nMaxWidth; // max string width

    long m_nFirstShowCharacterIndex; // the first character to output the line

    CXI_IMAGE *m_pLeftImage;
    CXI_IMAGE *m_pRightImage;
    CXI_IMAGE *m_pMiddleImage;

    bool m_bWaitKeyRelease;
    bool m_bDisguiseString;

    std::string m_sExcludeChars;
};
