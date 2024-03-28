using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Rigidbody))]
public class RigidBodyMovement : MonoBehaviour
{
    Rigidbody rb;
    [SerializeField] Vector3 force;
    [SerializeField] Vector3 torqe;
    [SerializeField] ForceMode mode;
    [SerializeField] ForceMode torqeMode;
    [SerializeField] KeyCode jumpKey;

    void Start()
    {
        rb = GetComponent<Rigidbody>();        
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(jumpKey))
        {
            rb.AddForce(Vector3.up, ForceMode.Impulse);
        }
    }

    private void FixedUpdate()
    {
        if (Input.GetKey(KeyCode.Space)) 
        {
            rb.AddForce(force, mode);
            rb.AddTorque(torqe, torqeMode);
        }
    }


}
