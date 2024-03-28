using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Aim : MonoBehaviour
{
    [SerializeField] float speed = 3;
    Vector3 rotation = Vector3.zero;
    Vector2 prevAxis = Vector2.zero;
    void Start()
    {
        prevAxis.y = Input.GetAxis("Mouse X");
        prevAxis.x = Input.GetAxis("Mouse Y");

        Cursor.lockState = CursorLockMode.Locked;
        Cursor.visible = false;
    }

    void Update()
    {
        Vector3 axis = Vector3.zero;
        axis.y = Input.GetAxis("Mouse X") - prevAxis.y;
        axis.x = Input.GetAxis("Mouse Y") - prevAxis.x;

        rotation.x += axis.x * speed;
        rotation.y += axis.y * speed;

        rotation.x = Mathf.Clamp(rotation.x, -50, 50);
        rotation.y = Mathf.Clamp(rotation.y, -70, 70);

        Quaternion qyaw = Quaternion.AngleAxis(rotation.y * speed, Vector3.up);
        Quaternion qpitch = Quaternion.AngleAxis(rotation.x * speed, Vector3.right);

        transform.rotation *= (qyaw * qpitch);
    }
}
