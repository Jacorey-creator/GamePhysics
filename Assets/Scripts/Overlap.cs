using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Overlap : MonoBehaviour
{
    public enum eType
    {
        BoundingBox,
        Sphere
    }
    [SerializeField] float size = 1.0f;
    [SerializeField] eType type = eType.BoundingBox;
    [SerializeField] LayerMask layerMask = Physics.AllLayers; //0,0,0,0,0

    Collider[] colliders;
    void Update()
    {
        switch (type)
        {
            case eType.BoundingBox:
                Physics.OverlapBox(transform.position, Vector3.one * size * 0.5f, transform.rotation, layerMask);
                break;
            case eType.Sphere:
                Physics.OverlapSphere(transform.position, size * 0.5f, layerMask);
                break;
        }
        if (Input.GetKey(KeyCode.Space))
        {
            Physics.gravity = new Vector3(0, 10, 0);
        }
        else 
        {
            Physics.gravity = new Vector3(0, 9.81f, 0);
        }
    }
    private void OnDrawGizmos()
    {
        Gizmos.color = Color.green;
        switch (type)
        {
            case eType.BoundingBox:
                Gizmos.DrawWireCube(transform.position, Vector3.one * size);
                break;
            case eType.Sphere:
                Gizmos.DrawWireSphere(transform.position, size * 0.5f);
                break;
        }

        Gizmos.color = Color.red;
        if (colliders != null)
        {
            foreach (var collider in colliders)
            {
                Gizmos.DrawWireCube(collider.bounds.center, collider.bounds.size);
            }
        }
    }

}
