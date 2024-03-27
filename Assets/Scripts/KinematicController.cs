using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class KinematicController : MonoBehaviour
{
    [SerializeField] float speed = 1.0f;
    [SerializeField] Space space = Space.World;
    // Update is called once per frame
    void Update()
    {
        Vector3 direction = Vector3.zero;
        float rotation = 0;

        if (space == Space.World) direction.x = Input.GetAxis("Horizontal");
        else 
        {
           rotation  = Input.GetAxis("Horizontal");
        }
        direction.y = Input.GetAxis("Vertical");

        direction = Vector3.ClampMagnitude(direction, 1);

        transform.position += direction * speed * Time.deltaTime;

        transform.rotation *= Quaternion.Euler(0, rotation * speed, 0);
        direction = transform.rotation * direction;

        transform.Translate(direction * speed * Time.deltaTime, space);
    }
}
