using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

[RequireComponent(typeof(Rigidbody))]
public class Ammo : MonoBehaviour
{
    [SerializeField] float speed = 1;
    [SerializeField] float lifespan = 0;

    Rigidbody rb;

    private void Start()
    {
        if (lifespan > 0)
        {
            Destroy(gameObject, lifespan);
        }
        rb = GetComponent<Rigidbody>();
        //rb.AddForce(speed * Vector3.forward, ForceMode.VelocityChange);
        rb.AddRelativeForce(Vector3.forward * speed, ForceMode.VelocityChange);
    }
    private void FixedUpdate()
    {
        if (Input.GetKeyDown(KeyCode.UpArrow)) speed++;
        if (Input.GetKeyDown(KeyCode.DownArrow)) speed--;
    }
}
