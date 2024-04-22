using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScreenImageTarget : MonoBehaviour
{
    [SerializeField] Image image;
    [SerializeField] Camera view;
    [SerializeField] float distance = 5;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void LateUpdate()
    {
        Vector3 screen = image.transform.position;
        screen.z = distance;

        Vector3 worlds = view.ScreenToWorldPoint(screen);
    }
}
