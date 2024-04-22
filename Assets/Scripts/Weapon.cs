using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class Weapon : MonoBehaviour
{
    [SerializeField] GameObject ammo;
    [SerializeField] Transform emission;
    [SerializeField] AudioSource audioSource;

    public bool equipped = false;
    void Update()
    {
        Debug.DrawRay(emission.position, emission.forward * 10, Color.red);

        if (equipped && Input.GetMouseButtonDown(0))
        {
            if (audioSource != null) audioSource.Play();
            Instantiate(ammo, emission.position, emission.rotation);
        }
    }
}