using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{
    public float speed = 8f;            // the speed of the bullet's movement
    private Rigidbody bulletRigidbody;  // Rigidbody components to use for movement

    void Start()
    {
        // Locate the Rigidbody component in the game object and assign it to the bullet Rigidbody
        bulletRigidbody = GetComponent<Rigidbody>();
        // Rigidbody Speed = Forward * Moving Speed
        bulletRigidbody.velocity = transform.forward * speed;
        // Destroy your game object in 3 seconds
        Destroy(gameObject, 3f);
    }

    // Method that is automatically executed in the event of a trigger crash
    void OnTriggerEnter(Collider other)
    {
        // The conflicting opponent's game object has a Player tag
        if (other.tag=="Player")
        {
            // Import PlayerController Components from an Opponent Game Object
            PlayerController playerController = other.GetComponent<PlayerController>();
            // If you have successfully imported the Player Controller components from the other party,
            if (playerController!=null)
            {
                // Run the Die() method of the counterpart playerController component
                playerController.Die();
            }
        }
    }
}
