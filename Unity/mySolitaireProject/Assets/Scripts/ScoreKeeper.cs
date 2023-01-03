using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoreKeeper : MonoBehaviour
{
    public Selectable[] topStacks;
    public GameObject highScorePanel;
    public float playTime;
    public Text textTime;
    // Start is called before the first frame update
    void Start()
    {
        playTime = 0;
    }

    // Update is called once per frame
    void Update()
    {
        playTime += Time.deltaTime;
        textTime.text = "Time : " + Mathf.Round(playTime);

        if(HasWon())
        {
            Win();
        }
    }

    public bool HasWon()
    {
        int i = 0;
        foreach(Selectable topStack in topStacks)
        {
            i += topStack.value;
        }
        if(i>=52)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void Win()
    {
        highScorePanel.SetActive(true);
        print("You have won!");
    }
}
