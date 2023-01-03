using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIButtons : MonoBehaviour
{
    public GameObject highScorePanel;
    public ScoreKeeper gamePlayTime;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void PlayAgain()
    {
        highScorePanel.SetActive(false);
        gamePlayTime.playTime = 0;
        ResetScene();
    }

    public void ResetScene()
    {        
        UpdateSprite[] cards = FindObjectsOfType<UpdateSprite>();
        foreach (UpdateSprite card in cards)
        {
            Destroy(card.gameObject);
        }
        ClearTopValue();
        FindObjectOfType<Solitaire>().PlayCards();
    }

    void ClearTopValue()
    {
        Selectable[] selectables = FindObjectsOfType<Selectable>();
        foreach (Selectable selectable in selectables)
        {
            if (selectable.CompareTag("Top"))
            {
                selectable.suit = null;
                selectable.value = 0;
            }
        }
    }

    public void isHardOption()
    {
        Solitaire option = FindObjectOfType<Solitaire>();
        if (option.HardOption==false)
        {
            option.HardOption = true;
        }
        else
        {
            option.HardOption = false;
        }
        ResetScene();
    }
}
