using UnityEngine;
using System.Collections;

public class UIScript : MonoBehaviour {
	
	private TextMesh scoreText = null;
	private PlayerMovement pHorse = null;
	
	// Use this for initialization
	void Start () {
		scoreText = gameObject.GetComponent<TextMesh>();
		pHorse = GameObject.Find("Horse").GetComponent<PlayerMovement>();
	}
	
	// Update is called once per frame
	void Update () {
		scoreText.text = "Score: " + pHorse.GetScore().ToString();
	}
}
