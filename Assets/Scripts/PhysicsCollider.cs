using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PhysicsCollider : MonoBehaviour
{
    string status;
    Vector3 contact;
    Vector3 normal;
    //COLLIDE
    private void OnCollisionEnter(Collision collision)
    {
        status = "collision enter " + collision.gameObject.name;
    }
    private void OnCollisionStay(Collision collision)
    {
        status = "collision " + collision.gameObject.name;

    }
    private void OnCollisionExit(Collision collision)
    {
        status = "collision exit " + collision.gameObject.name;

    }
    //TRIGGER
    private void OnTriggerEnter(Collider other)
    {
        status = "triger enter " + other.gameObject.name;

    }
    private void OnTriggerStay(Collider other)
    {
        status = "triger  " + other.gameObject.name;

    }
    private void OnTriggerExit(Collider other)
    {
        status = "triger exit " + other.gameObject.name;

    }
    //GUI
    private void OnGUI()
    {
        GUI.skin.label.fontSize = 16;
        Vector2 screen = Camera.main.WorldToScreenPoint(transform.position);
        GUI.Label(new Rect(screen.x, Screen.height - screen.y, 250, 70), status);
    }
    private void OnDrawGizmos()
    {
        Gizmos.color = Color.red;
        Gizmos.DrawSphere(contact, 0.1f);
        Gizmos.DrawLine(contact, contact + normal);
    }
}
