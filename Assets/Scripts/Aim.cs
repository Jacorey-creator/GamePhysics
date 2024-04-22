
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Aim : MonoBehaviour
{
    [SerializeField] float speed = 3;
    [SerializeField] float pitchLimit = 50;
    [SerializeField] float yawLimit = 50;

    Vector3 rotation = Vector3.zero;

    void Start()
    {
        Cursor.lockState = CursorLockMode.Locked;
        Cursor.visible = false;
    }

    void Update()
    {
        Vector3 axis = Vector3.zero;
        axis.x = -Input.GetAxis("Mouse Y");
        axis.y = Input.GetAxis("Mouse X");

        rotation.x += axis.x * speed;
        rotation.y += axis.y * speed;

        rotation.x = Mathf.Clamp(rotation.x, -pitchLimit, pitchLimit);
        rotation.y = Mathf.Clamp(rotation.y, -yawLimit, yawLimit);

        //rotation.x = Mathf.Clamp(rotation.x, -180, 180);
        //rotation.y = Mathf.Clamp(rotation.y, -90, 90);

        Quaternion qyaw = Quaternion.AngleAxis(rotation.y * speed, Vector3.up);
        Quaternion qpitch = Quaternion.AngleAxis(rotation.x * speed, Vector3.right);

        transform.localRotation = qyaw * qpitch;
    }
}