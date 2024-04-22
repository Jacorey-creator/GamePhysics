using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Animations.Rigging;

[RequireComponent(typeof(CharacterController))]
public class CharacterMovement : MonoBehaviour
{
    [SerializeField] float playerSpeed = 2.0f;
    private float tempPlayerSpeed = 2.0f;
    [SerializeField] float jumpHeight = 1.0f;
    [SerializeField] float pushPower = 2.0f;
    [SerializeField] Transform cameraView;
    [SerializeField] Rig rig;
    private CharacterController controller;
    private Vector3 velocity;
    private bool groundedPlayer;

    [SerializeField] Animator animator;
    private float YVelocity;
    private bool Equipped;
    private bool onGround;

    private void Start()
    {
        controller = gameObject.GetComponent<CharacterController>();
        animator = gameObject.GetComponent<Animator>();
    }

    void Update()
    {
        bool isButtonHeld = false;
        float holdStartTime = 0f;
        groundedPlayer = controller.isGrounded;
        if (groundedPlayer && velocity.y < 0)
        {
            velocity.y = 0f;
        }
        //if (Input.GetKeyDown(KeyCode.E))
        //{
        //    animator.GetBool("Equipped", !animator.GetBool("Equipped"));
        //}
        Vector3 move = new Vector3(Input.GetAxis("Horizontal"), 0, Input.GetAxis("Vertical"));
        //View Space
        move = Vector3.ClampMagnitude(move, 1);
        move = Quaternion.Euler(0, cameraView.rotation.eulerAngles.y, 0) * move;

        controller.Move(move * Time.deltaTime * playerSpeed);

        if (move != Vector3.zero)
        {
            //gameObject.transform.forward = move;
            transform.rotation = Quaternion.Slerp(transform.rotation, Quaternion.LookRotation(move), Time.deltaTime);
        }

            //Set Walk Animation
            isButtonHeld = true;
            holdStartTime = Time.time;

            animator.SetFloat("Speed", move.magnitude * playerSpeed);
            animator.SetFloat("YVelocity", velocity.y);
            animator.SetBool("OnGround", onGround);
        
        
 

        //Changes Height of the player
        if (Input.GetButton("Jump") && groundedPlayer)
        {
            velocity.y += Mathf.Sqrt(jumpHeight * -2.0f * Physics.gravity.y);
        }
        if (Input.GetKeyDown(KeyCode.E)) 
        {
            animator.SetBool("Equipped", !animator.GetBool("Equipped"));
        }

        velocity.y += Physics.gravity.y * Time.deltaTime;
        controller.Move(velocity * Time.deltaTime);
    }

    // this script pushes all rigidbodies that the character touches
    void OnControllerColliderHit(ControllerColliderHit hit)
    {
        Rigidbody body = hit.collider.attachedRigidbody;

        // no rigidbody
        if (body == null || body.isKinematic)
        {
            return;
        }

        // We dont want to push objects below us
        if (hit.moveDirection.y < -0.3)
        {
            return;
        }

        // Calculate push direction from move direction,
        // we only push objects to the sides never up and down
        Vector3 pushDir = new Vector3(hit.moveDirection.x, 0, hit.moveDirection.z);

        // If you know how fast your character is trying to move,
        // then you can also multiply the push velocity by that.

        // Apply the push
        body.velocity = pushDir * pushPower;
    }

}