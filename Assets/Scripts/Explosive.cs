using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

public class Explosive : MonoBehaviour
{
    [SerializeField] private float _triggerForce = 0.5f;
    [SerializeField] private float _explosionRadius = 5.0f;
    [SerializeField] private float _explosionForce = 100.0f;
    private int _explosionCount = 0;
    [SerializeField] private GameObject particleEffect;

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.relativeVelocity.magnitude >= _triggerForce)
        {
            var surroundingObjects = Physics.OverlapSphere(transform.position, _explosionRadius);
        }

        Instantiate(particleEffect, transform.position, Quaternion.identity);
        DestroyAfterDelay();

    }
    private void OnTriggerEnter(Collider other)
    {
        if (!other.gameObject.isStatic && _explosionCount < 2)
        {
            Instantiate(particleEffect, transform.position, Quaternion.identity);
            _explosionCount++;
        }

    }
    IEnumerator DestroyAfterDelay()
    {
        // Wait for the specified delay
        yield return new WaitForSeconds(1);

        // Destroy the object immediately
        DestroyImmediate(particleEffect);

    }
}
