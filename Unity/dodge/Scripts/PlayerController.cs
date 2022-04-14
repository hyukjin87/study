using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    private Rigidbody playerRigidbody;  // Rigidbody components to use for movement
    public float speed = 8f;            // moving speed

    void Start()
    {
        // Locate the Rigidbody component in the game object and assign it to the playerRigidbody
        playerRigidbody = GetComponent<Rigidbody>();
    }

    void Update()
    {
        // Detects and stores inputs on horizontal and vertical axes
        float xInput = Input.GetAxis("Horizontal");
        float zInput = Input.GetAxis("Vertical");

        // Determine the actual travel speed using the input and travel speed
        float xSpeed = xInput * speed;
        float zSpeed = zInput * speed;

        // Generate Vector3 speed in (xSpeed, 0, zSpeed)
        Vector3 newVelocity = new Vector3(xSpeed, 0f, zSpeed);
        // Assign a new Velocity to the speed of the rigidbody
        playerRigidbody.velocity = newVelocity;

        //if(Input.GetKey(KeyCode.UpArrow)==true)
        //{
        //    playerRigidbody.AddForce(0f, 0f, speed);
        //}
        //if(Input.GetKey(KeyCode.DownArrow)==true)
        //{
        //    playerRigidbody.AddForce(0f, 0f, -speed);
        //}
        //if(Input.GetKey(KeyCode.RightArrow)==true)
        //{
        //    playerRigidbody.AddForce(speed, 0f, 0f);
        //}
        //if (Input.GetKey(KeyCode.LeftArrow) == true)
        //{
        //    playerRigidbody.AddForce(-speed, 0f, 0f);
        //}
    }

    public void Die()
    {
        gameObject.SetActive(false);
        GameManager gameManager = FindObjectOfType<GameManager>();
        gameManager.EndGame();
    }
}
