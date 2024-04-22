using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Caster : MonoBehaviour
{
    public enum eType
    {
        RAY,
        SPHERE,
        BOX
    }
    [SerializeField] eType type = eType.RAY;
    [SerializeField] float distance = 2;
    [SerializeField] float size = 1;
    [SerializeField] LayerMask layerMask = Physics.AllLayers;

    RaycastHit[] raycastHits;
    // Update is called once per frame
    void Update()
    {
        Vector3 forward = transform.rotation * new Vector3(0, 0, 0);
        switch (type)
        {
            case eType.RAY:
                raycastHits = Physics.RaycastAll(transform.position, Vector3.forward, distance, layerMask);
                break;
            case eType.SPHERE:
                raycastHits = Physics.SphereCastAll(transform.position, size * 0.5f, transform.forward, distance, layerMask);
                break;
            case eType.BOX:
                raycastHits = Physics.BoxCastAll(transform.position, Vector3.one * size * 0.5f, transform.forward, transform.rotation, distance, layerMask);

                break;
        }
    }

    private void OnDrawGizmos()
    {
        Gizmos.color = Color.blue;
        Gizmos.DrawRay(transform.position, transform.forward * distance);

        if (raycastHits != null)
        {
            Gizmos.color = Color.red;
            foreach (var hit in raycastHits)
            {
                Gizmos.DrawWireCube(hit.point, hit.collider.bounds.size);
            }
        }
        switch (type)
        {
            case eType.RAY:
                Gizmos.DrawRay(transform.position, transform.forward * distance);
                    break;
            case eType.SPHERE:
                Gizmos.DrawRay(transform.position, transform.forward * distance);
                Gizmos.DrawWireSphere(transform.position + transform.forward * distance, size * 0.5f);
                break;
            case eType.BOX:
                Gizmos.DrawRay(transform.position, transform.forward * distance);
                Gizmos.DrawWireCube(transform.position + transform.forward * distance, Vector3.one * size);
                break;
        }
    }
}
