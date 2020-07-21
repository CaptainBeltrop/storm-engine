#include "DIALOGS\russian\Common_Duel.c" //navy
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
    ref NPChar, d;
	aref Link, Diag;
	string NPC_Meeting, TempInfoCharacterID_1, TempInfoCharacterID_2;
	int DonationSize;
    	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
    ProcessCommonDialogRumors(NPChar, Link, Diag);//homo 25/06/06
    ProcessDuelDialog(NPChar, Link, Diag); //navy

	int iEnemyDice, iPCDice;
	// boal 13.03.2004 -->
	int d1,d2,d3,d4;
	bool ok;
	// boal 13.03.2004 <--
    ref sld;
    
	if (npchar.quest.Meeting != LastSpeakDate())
	{
		npchar.quest.last_theme = makeint(rand(1));
		npchar.quest.last_theme_game = makeint(rand(1));
		npchar.quest.Meeting = LastSpeakDate();
		npchar.money = 100 + rand(10) * makeint(50 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
        if (bBettaTestMode)
        {
            Dialog.CurrentNode = "Beta_test";
        }
	}
	
	switch (Dialog.CurrentNode)
	{
		// -----------------------------------������ ������ - ������ �������
		
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

        case "Beta_test":
            dialog.text = "��� ���� ������ ���� ����� (��������)";
			link.l1 = "����� ����� �����";
			link.l1.go = "Beta_test_alc";
            link.l2 = "����� � �����";
			link.l2.go = "Beta_test_card";
			link.l3 = "����� � �����";
			link.l3.go = "Beta_test_dice";
		break;
		
		case "Beta_test_alc":
            dialog.text = "����� ������";
			link.l1 = "����������";
			link.l1.go = "First time";
			npchar.quest.last_theme = 0;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_card":
            dialog.text = "����� � ����� (30%% ��� ������ � ������� ����)";
			link.l1 = "����������";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_dice":
            dialog.text = "����� � ����� (30%% ��� ������ � ������� ����)";
			link.l1 = "����������";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 1;
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = LinkRandPhrase("�, �����, � ����, �� � ����� ���. ������ ��� ����� � �����, � ������� � ���� ��������! ��-�-��...", "� �� ���� ������, � ������� ����. �� ���� � ����� ����!" , "��������, ���� ����� �� �������� ������ �������-���������...");
				link.l1 = RandPhraseSimple("�� ��� ������...", "���, ������ ���� ����� ��������! �� �� �����."); 
				link.l1.go = "exit";
				break;
			}
            ok = CheckFreeSitFront(npchar); //checkAttribute(npchar, "Default.ToLocator"); // ���� ���� �����
            
            dialog.text = "�� ����������� ��� ����, ��� � ������ �� �����!";
            link.l1 = "��� ������...";
		    link.l1.go = "exit";
		    if (!chrDisableReloadToLocation)
		    {
	            switch (npchar.quest.last_theme)
				{
					case "0": //������.
						dialog.text = "�-��! �, ������, �� ��������� ������� ������� ������! �����, ������ ��� ��������� ����?";
						link.l1 = "����� � � ������� ����, ������ ��� �� ������, ��� � ���� ����� ������ �����...";
						link.l1.go = "exit";

						if (makeint(pchar.money) >= 100 && ok) // ������ ������ ������� ������� �� �����
						{
							link.l2 = "� � ��� � �������� ������������ � ����, �� ��������.";
							link.l2.go = "talk_with_alchogol";
						}
						else
						{
	                        link.l2 = "��� ��� ������?";
							link.l2.go = "talk_with_alchogol_song";
						}
					break;

					case "1":
	                    if (rand(3) != 1 && ok)
	                    {
							switch (sti(npchar.quest.last_theme_game))
							{
							    case 0 :
									// ���� � ����� boal 20/05/05 -->
	                                if (CheckNPCQuestDate(npchar, "Card_date_begin"))
									{
										Dialog.text = RandPhraseSimple("������� � �����, ����� ���������� ����?", "��������� ������������ � ��������. �� ���?");
										link.l1 = "������ �� �� �������? ����� �������.";
										link.l1.go = "Cards_begin";
										link.l2 = "� ������� � ���� �����?";
										link.l2.go = "Cards_Rule";
										link.l3 = "�� ������.";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "���, �� ���� � ������ ������ � ����� � �����.";
						    			link.l1 = "�� � �� ����.";
						    			link.l1.go = "exit";
									}
			                        // ���� � ����� boal 20/05/05 <--
		                        break;

								case 1:
								// �����
		    						// ���� � ����� boal 13/07/05 -->
	                                if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
									{
										Dialog.text = RandPhraseSimple("������� � �����, ����� ���������� ����?", "��������� ��������� ����������. �� ���?");
										link.l1 = "������ �� �� �������? ����� �������.";
										link.l1.go = "Dice_begin";
										link.l2 = "� ������� � ���� �����?";
										link.l2.go = "Dice_Rule";
										link.l3 = "�� ������.";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "���, �� ���� � ������ ������ � ����� � �����.";
					    				link.l1 = "�� � �� ����.";
					    				link.l1.go = "exit";
									}
			                        // ���� � ����� boal 13/07/05 <--
			                        //navy --> �����
									if (CheckAttribute(NPchar, "Quest.DiceCheats") && sti(NPchar.Quest.DiceCheats) >= 1) // && sti(NPChar.Quest.HeroLose))
									{
					    				link.l9 = RandSwear() + " �� ���������!!!";
					    				link.l9.go = "outraged";
									}
									//navy <--
			    				break;
	    					} //switch
						}
	        			else
	        			{
	                        dialog.text = RandPhraseSimple("�������� �� ����� ����� �� ���� ������!", " �.. ����? ��� ���?.. �-��.. ������!");
	                        link.l1 = RandPhraseSimple("�������� ����� ���� ������� ���� - ��������!", "�� ����� ��� �������.");
	        			    link.l1.go = "exit";
	        			    link.l2 = RandPhraseSimple("��� �� �� ���� ��������������, �������! ������ � ����� ���� ������� �������.", "��� � ������ ���� ������ �� �����, ���� ������������.");
	        	            link.l2.go = "tavern_keeper";
	        			}
					break;
				}
			}
			Diag.TempNode = "First time";
	    break;
	    
	    // ����� -->
	    case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "��� �, ����� ������!";
			link.l1.go = "Cards_begin";
			link.l3 = "���, ��� �� ��� ����...";
			link.l3.go = "exit";
		break;
		
		case "Cards_begin":
			Diag.tempnode = "Cards_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Cards_Node":
			Diag.tempNode = "first time";

			Dialog.text = "����� ����������� �� �������.";
			link.l1 = "������ �� 100 �����";
			link.l1.go = "Cards_Node_100";
			link.l2 = "����� �� 500 �������";
			link.l2.go = "Cards_Node_500";
			link.l3 = "�������, ��� ����.";
			link.l3.go = "exit_sit";
		break;
		
		case "Cards_Node_100":
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = "� ���� ����� ����� ���������������� ������. � �� ���� � ����� ������ � ����� ������.";
                link.l1 = "��� ����! �� � �� �����.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		    
			if (sti(pchar.Money) < 300)
		    {
                dialog.text = "�� ��, ������, �� ����. ������������, �������.";
                link.l1 = "�����.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "� ��� ���������� � ��� � ����, �� ��� ����.";
                link.l1 = "�����.";
			    link.l1.go = "exit_sit";
			    break;
		    }
   			dialog.text = "������, ������ �� 100 �����.";
			link.l1 = "������!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 100;
            pchar.GenQuest.Cards.SitType   = true;
		break;
		
		case "Cards_Node_500":
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = "� ���� ����� ����� ���������������� ������. � �� ���� � ����� ������ � ����� ������.";
                link.l1 = "��� ����! �� � �� �����.";
			    link.l1.go = "exit_sit";
			    break;
		    }
			if (!CheckCardsGameBigRate())
		    {
                dialog.text = "� ������, ��� �� ����� ������ �������. � �� ���� ������ � ����� �� ����� ������� �������.";
                link.l1 = "����� �� ����� ������?";
			    link.l1.go = "Cards_Node_100";
				link.l2 = "�� � �� �����.";
			    link.l2.go = "exit_sit";
			    break;
		    }
		    
			if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "�� ��, ������, �� ����. ������������, �������.";
                link.l1 = "�����.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "� ��� ���������� ��� ����� ������� ������, ���� �� ��� ����.";
                link.l1 = "����.";
			    link.l1.go = "exit_sit";
			    break;
		    }
   			dialog.text = "������, ������ �� 500 �����.";
			link.l1 = "������!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 500;
            pchar.GenQuest.Cards.SitType   = true;
		break;
		
		case "Cards_begin_go":
            // ����� ���� � ���� SetNPCQuestDate(npchar, "Card_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // ����� <--
	    // ����� -->
	    case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "��� �, ����� ������!";
			link.l1.go = "Dice_begin";
			link.l3 = "���, ��� �� ��� ����...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Diag.tempnode = "Dice_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Dice_Node":
		    Diag.tempNode = "first time";
		    
			Dialog.text = "����� ����������� �� �������.";
			link.l1 = "������ �� 50 ����� �� �����";
			link.l1.go = "Dice_Node_100";
			link.l2 = "����� �� 200 ������� �� �����";
			link.l2.go = "Dice_Node_500";
			link.l3 = "�������, ��� ����.";
			link.l3.go = "exit_sit";
		break;

		case "Dice_Node_100":
            if (!CheckDiceGameSmallRate())
		    {
                dialog.text = "� ���� ����� ����� ���������������� ������. � �� ���� � ����� ������ � ������ ������.";
                link.l1 = "��� ����! �� � �� �����.";
			    link.l1.go = "exit_sit";
			    break;
		    }

			if (sti(pchar.Money) < 300)
		    {
                dialog.text = "�� ��, ������, �� ����. ������������, �������.";
                link.l1 = "�����.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "� ��� ���������� � ��� � ����, �� ��� ����.";
                link.l1 = "�����.";
			    link.l1.go = "exit_sit";
			    break;
		    }
   			dialog.text = "������, ������ �� 50 �����.";
			link.l1 = "�������!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 50;
            pchar.GenQuest.Dice.SitType   = true;
		break;

		case "Dice_Node_500":
            if (!CheckDiceGameSmallRate())
		    {
                dialog.text = "� ���� ����� ����� ���������������� ������. � �� ���� � ����� ������ � ����� ������.";
                link.l1 = "��� ����! �� � �� �����.";
			    link.l1.go = "exit_sit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "� ������, ��� �� ����� ������ �������. � �� ���� ������ � ����� �� ����� ������� �������.";
                link.l1 = "����� �� ����� ������?";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "�� � �� �����.";
			    link.l2.go = "exit_sit";
			    break;
		    }

			if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "�� ��, ������, �� ����. ������������, �������.";
                link.l1 = "�����.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "� ��� ���������� ��� ����� ������� ������, ���� �� ��� ����.";
                link.l1 = "����.";
			    link.l1.go = "exit_sit";
			    break;
		    }
   			dialog.text = "������, ������ �� 200 �����.";
			link.l1 = "�������!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 200;
            pchar.GenQuest.Dice.SitType   = true;
		break;

		case "Dice_begin_go":
            // ����� ���� � ���� SetNPCQuestDate(npchar, "Dice_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // ����� <--
	    // homo 01/08/06 to_del
        // ������� �� ����� - ������� � �����
	    //case "Find_Merchant_1":
            //if (pchar.GenQuest.Find_Merchant.lastspeak_date == LastSpeakDate())
            //{
            //    dialog.text = "� �� ��� �� ������������? �-��! �� �� ����� �� ��?";
    		//	link.l1 = "������! ���� �����������.";
    	//		link.l1.go = "exit_sit";
            /*}    // to_do
            else
            {
                pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
                MerchantOnMap();
                sld = characterFromID("Quest_Merchant");
       			dialog.text = "������ � ���� " + RandPhraseSimple("������", "�����") + " �� ������� '" + sld.Ship.Name +
                              "' ��� ������ " + NationNameGenitive(sti(sld.nation)) + " ����� ������ ���� " + GetGoodsNameAlt(sti(sld.QuestGoodsIdx)) + ".";
    			link.l1 = "�������, ������! ���� ��� � ����, ��������� � ���.";
    			link.l1.go = "exit_sit";
			} */
		//break;
		//////  1
	    case "GhostShip_Speak_1":
            npchar.GhostShip_Speak_Yet = true;
            pchar.GenQuest.GhostShip.lastspeak_date = LastSpeakDate();
   			dialog.text = "��... �-��! ����� � �������� - �������-�������, � �� ��� �������� ��������... �������, �� ��� �� ������ ������� �������...";
			link.l1 = "�� ����� ������!";
			link.l1.go = "GhostShip_Speak_1_2";
		break;
		
		case "GhostShip_Speak_1_2":
			dialog.text = "� ���? �-��! �� � ������ ������ ���, ���� ������, ��� �����... ��� �� �� ������ ������ ������� ������ � �����...";
			link.l1 = "� ��� �� �� ������?";
			link.l1.go = "GhostShip_Speak_1_3";
		break;
		
		case "GhostShip_Speak_1_3":
			dialog.text = "�� � ��� ������, ��� ��� � ������ ��������, �� ����� �������� �-��!... � �� �� ������ - ��� �� ��������! � �����, ������, ��������...";
			link.l1 = "���.. ���� �� ��������, ������ ������ ������";
			link.l1.go = "exit_sit";
			pchar.GenQuest.GhostShip.AskAbout = "1";
			AddQuestRecord("GhostShipQuest", pchar.GenQuest.GhostShip.AskAbout);
		break;
		//////  2
		case "GhostShip_Speak_2":
            npchar.GhostShip_Speak_Yet = true;
            pchar.GenQuest.GhostShip.lastspeak_date = LastSpeakDate();
            dialog.text = "������? �� �� ��� ������?.. � ��� ������� ������� ��������� ����� ������� ������� ������ �� ���.";
			link.l1 = "����� ��� ���������?";
			link.l1.go = "GhostShip_Speak_2_2";
		break;

		case "GhostShip_Speak_2_2":
			dialog.text = "'�������'! ��� �������-������� ����� �������� � ����������. ����� �������� �� ����� ���... � ����������� ��� �� �����. � �� ��� �������� ��� �� ��� � ���� �� �� �����.";
			link.l1    = "� ��� ��, �� ����� ������?";
			link.l1.go = "GhostShip_Speak_2_3";
		break;

		case "GhostShip_Speak_2_3":
			dialog.text = "������, ������ ����� �������, ���� �������� ����� ��������, � ������-�� � ����� ����! ����, � ������, ������ �� ���-��, �� �� ��, ���������� ��������� - �� ��� �� ������ ������� �������, ��������� ���-��� � ����� ����������.";
			link.l1 = "��, �� ���� ���� ������� ����������... '�� ��� �����' - ���� ��. ����, �������, ���������� �������.";
			link.l1.go = "exit_sit";
			pchar.GenQuest.GhostShip.AskAbout = "2";
			AddQuestRecord("GhostShipQuest", "2");
		break;
		//////  3
		case "GhostShip_Speak_3":
            npchar.GhostShip_Speak_Yet = true;
            pchar.GenQuest.GhostShip.lastspeak_date = LastSpeakDate();
            
			if (!CheckAttribute(pchar, "GenQuest.GhostShip.LastBattle") &&
                             CheckAttribute(pchar, "GenQuest.GhostShip.NeedCoins")  &&
                            !CheckAttribute(npchar, "quest.GhostShipHelp")          &&
                            !CheckAttribute(pchar, "GenQuest.GhostShipWorkId")      &&
                            rand(2) == 1)
            {
                dialog.text = "��� ��, ������� ��� ����� �������� ���� ��������. ����� �� ����, ��������� ����������������, ����� ���� ������ �����.";
                link.l1 = "� ���! �������, ��� ����.";
    			link.l1.go = "exit_sit";
                break;
            }

            dialog.text = "������� ���������? �� ���� ����� �������, ���� ������ �� �����.";
            if (sti(PChar.GenQuest.GhostShip.KillMe) > 0 || sti(PChar.GenQuest.GhostShip.DeadByMe) > 0)
            {
                link.l1 = "�� � ��� ��� �����! ��� ��� �������. ��� ��� �����?";
            }
            else
            {
				link.l1 = "�����, � ����. ��� ��� �����?";
			}
			link.l1.go = "GhostShip_Speak_3_2";
		break;

		case "GhostShip_Speak_3_2":
			dialog.text = "��� ������� �������������� ��������, ��� ����� �� � ���� ����� �������.";
			link.l1    = "����� �����, �����? �� ��� ���?";
			link.l1.go = "GhostShip_Speak_3_3";
		break;

		case "GhostShip_Speak_3_3":
			dialog.text = "������ ��� �����, � ���� ���� ��������. �������������� ���� �������, ���� ����� ��������...";
    		if (sti(PChar.GenQuest.GhostShip.KillMe) > 0 || sti(PChar.GenQuest.GhostShip.DeadByMe) > 0)
            {
                link.l1 = "��� ��, �������� ��� �������, ��� �������� � ��� �� ��������!";
            }
            else
            {
				link.l1 = "��� ��, �������� ��� �������, ���������� ��� ��� �� �������.";
			}
			link.l1.go = "exit_sit";
			pchar.GenQuest.GhostShip.AskAbout = "2";// ������ ���������
			AddQuestRecord("GhostShipQuest", "3");
			GhostShipOnMap();
		break;
		/////////////////////////////////////////////
        case "talk_with_alchogol_song":
			dialog.text = "��... �-��! ������ ��� �� ����� ������.. �-��! � ��� ���� ����� �� �������.. �-��! � ������ ������ ��� �����.. �-��! �������� ������ ���.. �-��!\n ����������, �������!";
			link.l1 = "� ������?";
			link.l1.go = "talk_with_alchogol_song_2";
			link.l2 = "�� �� ����!";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_2":
			dialog.text = "�������� ������, ����, �������.. �-��! � ����� �� �����. � ��� ������ �� ����� � �����.. �-��! ��� �������? �����!";
			link.l1 = "� ������?";
			link.l1.go = "talk_with_alchogol_song_3";
			link.l2 = "�� �� ����!";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_3":
			dialog.text = "����� �� ������ ������� � ������� � �����, �� ���� ������ ���� �� ����� ���� �����! � ��� ����� � ������ ��� ������ ����� ������. ������� ��, ��� � ������ ���� � ����� ����!";
			link.l1 = "�� �� ����!";
			link.l1.go = "exit";
		break;
		
		case "talk_with_alchogol":
			Diag.TempNode = "begin_sit";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "begin_sit":
			Diag.TempNode = "first time";
			dialog.snd = "Voice\HADI\HADI028";
			dialog.text = "��! ���, ��� � �������! ��� ��� ��-������! ��, ��� ����? ��������� ��� �������� ����?";
			link.l1 = "�� ��������! ����������, ����!";
			link.l1.go = "sit_2";
		break;

		case "sit_2":
			AddMoneyToCharacter(pchar, -2);
			WaitDate("",0,0,0, 0, 30);
			dialog.text = LinkRandPhrase("�� ��������� ����! ����� �� ����������!",
			                             "��! ����� ���! ��... ���������!",
										 "�� ���� ��������, � �� ���� ��������!");
			link.l1 = "��, ���������� ���. �����, ��� ��� ����, ������ ��������.";
			link.l1.go = "exit_sit";
			if (makeint(pchar.money) >=2)
			{
				link.l2 = "����� ��� �� ����� ��������.";
				link.l2.go = "sit_3";
			}
			// homo 01/08/06 to_del
            // ������� �� ����� - ������� � �����
			//if (sti(pchar.reputation) < 41)
            //{
            //    link.l3 = "��� ����������� ������ ������� ��� '�������' ������ � ���� �����?";
			//	link.l3.go = "Find_Merchant_1";
            //}
            //homo 15/06/06 �����
            link.l4 = LinkRandPhrase("�������, ��� ������ � ���� ����� ��������. ��� ���������� � ����� �����?",
                                    "��������-�� ���, � ��� ������ �������? �� ��� �� � ��� ���� �����...",
                                    "����� ���, ������, ����� ����� ����� �� ��������?");
		    link.l4.go = "rumours_habitue";
		    //homo
		break;

		case "sit_3":
			int iSituation = makeint(rand(5));
			switch (iSituation)
			{
				case 0:
					dialog.text = "�! ������� ����!";
					link.l1 = "����������! ����!";
					link.l1.go = "sit_2";
				break;

				case 1:
					dialog.text = "��! ���... �������! �� �-������ ���� ������, ��! � ������� ��� ������!";
					link.l1 = "���������! �� ���� �����? � ���� ������������ ��������� ����!";
					link.l1.go = "sit_case_2_friend";
					link.l2 = "�! ��������, �����, ���� � ���� ����� �� ���������!";
					link.l2.go = "sit_case_2_enemy";
				break;

				case 2:
					dialog.text = "������! �� �-������� �������! �-����� ����, �-�� �������� ��� �... �... � ����� ������?";
					link.l1 = "��� �������, ��� ��� ���� ����.";
					link.l1.go = "exit_sit";
					link.l2 = "�-�������! ���� �� �� ��... ������!";
					link.l2.go = "sit_case_3";
				break;

				case 3:
					dialog.text = "...� ����� � ���-������� ��� ����� �� �-������ �...";
					link.l1 = "... � ��� ��� � �������...";
					link.l1.go = "sit_case_4_exit";
				break;

				case 4:
					dialog.text = "�� ����! �, ������! ��� ���?!";
					link.l1 = "�? ���? ���? ���������� ������.";
					link.l1.go = "sit_2";// to_do "sit_case_5_exit";
				break;
				
                case 5:
                    if (!CheckAttribute(pchar , "GenQuest.GhostShip.LastBattleEnd") && !checkAttribute(npchar, "GhostShip_Speak_Yet") && pchar.GenQuest.GhostShip.lastspeak_date != LastSpeakDate())
					{
                        dialog.text = "����� ��� �� ����� ��������.";
                        link.l1 = "��, ���������� ���. �����, ��� ��� ����, ������ ��������.";
						link.l1.go = "exit_sit";
						switch (sti(pchar.GenQuest.GhostShip.AskAbout))
						{
							case 0 :
								link.l2 = "����� ����� ����� �� ��������?";
								link.l2.go = "GhostShip_Speak_1";
							break;

							case 1 :
								link.l2 = "��� ����������� � ���� ����� ��������?";
								link.l2.go = "GhostShip_Speak_2";
							break;

							case 2 :
								link.l2 = "����� ���, ������, ��� �� ������ ��� �������-������� - '������� ���������'?";
								link.l2.go = "GhostShip_Speak_3";
							break;
						}
					}
					else
					{
	         			dialog.text = "���� ��� ����! ��� �����?";
						link.l1 = "�������!";
						link.l1.go = "sit_2";
					}
                break;
			}
		break;

		case "sit_case_5_exit": // �����
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("fighting");
		break;

		case "sit_case_4_exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("without_memory");
		break;

		case "sit_case_3":
			dialog.snd = "Voice\HADI\HADI037";
			dialog.text = "����� �-���, ��� �-���� �������� ���� �� �-������. �-���!";
			link.l1 = "�-������? �-���, � ������� ���.";
			link.l1.go = "exit_sit";
			link.l2 = "���������! �� ���� �����? � ���� ������������ ��������� ����!";
			link.l2.go = "sit_2";
		break;

		case "sit_case_2_friend":
			dialog.snd = "Voice\HADI\HADI038";
			dialog.text = "��? �-����� �� ��� ����?! �-���! �� ������... ��...  �� ������ ���� �����! �-���!";
			link.l1 = "�����, ����, ���� ��� ������ �� �������. ������.";
			link.l1.go = "exit_sit";
			link.l2 = "���? �� � ���� ������ ������, ��� � �� ���� ���� �������! � ���� ������ ����... ��... ������!";
			link.l2.go = "sit_case_2_friend_2";
		break;

		case "sit_case_2_friend_2":
			dialog.snd = "Voice\HADI\HADI039";
			dialog.text = "�-�-�! ������� ��� �� ����!!";
			link.l1 = "�� �� ���������... ��... ������ �� �����!";
			link.l1.go = "tavern_keeper";
		break;

		case "sit_case_2_enemy":
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "����! � ���� ��������, ��� ������!";
			link.l1 = "��� �� ��� ���������!";
//			link.l1.go = "tavern_keeper";
			link.l1.go = "fight_right_now"; //navy -- ����� � ������� ��� �������! :)
		break;

		case "exit_sit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;

		case "tavern_keeper":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("tavern_keeper");
		break;
	}
}

bool CheckFreeSitFront(ref _npchar)
{
 	ref rCharacter; //����
	int n;

	if (!CheckAttribute(_npchar, "Default.ToLocator")) return false;
	
	for (n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (CheckAttribute(rCharacter, "location") && rCharacter.location == _npchar.location)
		{
            if (rCharacter.location.locator == _npchar.Default.ToLocator)
                return  false;
		}
    }
    return  true;
}