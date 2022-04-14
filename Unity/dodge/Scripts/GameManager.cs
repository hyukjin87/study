using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;   
using UnityEngine.SceneManagement;  

public class GameManager : MonoBehaviour
{
    public GameObject gameoverText; // Text game object to activate in case of game
    public Text timeText;           // Text component to display survival time
    public Text recordText;         // Text component to display best records

    private float surviveTime;      // survival time
    private bool isGameover;        // Game Over Status

    void Start()
    {
        // Initialize survival time and game over status
        surviveTime = 0;
        isGameover = false;
    }

    void Update()
    {
        // While it's not a game over,
        if (!isGameover)
        {
            // Renew survival time
            surviveTime += Time.deltaTime;
            // Display updated survival time using timeText text components
            timeText.text = "Time: " + (int)surviveTime;
        }
        else
        {
            // If you pressed R while the game was over,
            if (Input.GetKeyDown(KeyCode.R))
            {
                // load the SampleScene
                SceneManager.LoadScene("SampleScene");
            }
        }
    }
    // Method to change the current game to Game Over
    public void EndGame()
    {
        // Switch current state to game over state
        isGameover = true;
        // Game over text Activate game objects
        gameoverText.SetActive(true);
        // Get previous best records stored with BestTime keys
        float bestTime = PlayerPrefs.GetFloat("BestTime");
        // If the current survival time is greater than the previous record,
        if (surviveTime>bestTime)
        {
            // Change the highest recording value to the current survival time value
            bestTime = surviveTime;
            // Save the highest changed history with the BestTime key
            PlayerPrefs.SetFloat("BestTime", bestTime);
        }
        // Display best records using recordText text components
        recordText.text = "Best Time: " + (int)bestTime;
    }
}
