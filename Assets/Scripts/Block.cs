using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.SocialPlatforms.Impl;

[RequireComponent(typeof(Rigidbody))]
public class Block : MonoBehaviour
{
    [SerializeField] int points = 100;
    [SerializeField] AudioSource audioSource;
    bool Destroyed = false;

    


    Rigidbody rb;
    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();
    }


    private void OnTriggerStay(Collider other)
    {
       
        if (!Destroyed && other.CompareTag("Kill")) 
        {
            Destroy(gameObject, 2);
            GameManager.Instance.AddScore(points);
            Destroyed = true;
            

        }
    }
   
}
