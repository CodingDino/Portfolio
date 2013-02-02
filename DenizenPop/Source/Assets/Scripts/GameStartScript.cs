using UnityEngine;
using System.Collections;

public class GameStartScript : MonoBehaviour {
	
	private static bool first_display = true;
	private bool title_done = false;

	private PlayerMovement		pHorse			= null;
	private MeatMonster			pMonster		= null;
	
	public	Texture2D				startTexture;
	public	Texture2D				instructionTexture;
	public	Texture2D				endTexture;
	
	// Use this for initialization
	void Start () {
		pHorse = GameObject.Find("Horse").GetComponent<PlayerMovement>();
		pMonster = GameObject.Find("MeatMonster").GetComponent<MeatMonster>();
		
		//startTexture = Resources.Load("Textures/splashscreen") as Texture2D;
	}
	
	// Update is called once per frame
	void Update () {
	}
	
	void OnGUI()
	{
		if(!pHorse.IsStarted() && !pHorse.IsFinished())
		{
			if(first_display)
			{
				
				// display start screen
				if (!title_done)
				{
					
					GUI.Label(new Rect(0.0f, 0.0f, 1126.4f, 844.8f), startTexture);
				
					// display start button
					if(GUI.Button(new Rect(462.0f, 250.0f, 100.0f, 50.0f), "START"))
					{
						title_done = true;
					}
				} else
				{ // Display instructions
					GUI.Label(new Rect(0.0f, 0.0f, 1126.4f, 844.8f), instructionTexture);
					if(Input.GetMouseButtonDown(0))
					{
						first_display = false;
						pHorse.GameStarted();
						pMonster.GameStart();
					}
				}
			}
			else 
			{
				pHorse.GameStarted();
				pMonster.GameStart();
			}
		}
		if(pHorse.IsStarted() && pHorse.IsFinished())
		{
			// display end screen
			GUI.Label(new Rect(0.0f, 0.0f, 1126.4f, 844.8f), endTexture);
			
			// display restart button
			if(GUI.Button(new Rect(462.0f, 250.0f, 100.0f, 50.0f), "RESTART"))
			{
				// RESTART
				Application.LoadLevel(0);
			}
			
			// Display scores
			GUI.Label(new Rect(462.0f, 350.0f, 100.0f, 50.0f), "Score = " + pHorse.GetScore().ToString());
			GUI.Label(new Rect(462.0f, 450.0f, 100.0f, 50.0f), "HIGH SCORES");
			// col1
			GUI.Label(new Rect(400.0f, 470.0f, 100.0f, 50.0f), "1.  "+PlayerMovement.high_scores[0]);
			GUI.Label(new Rect(400.0f, 490.0f, 100.0f, 50.0f), "2.  "+PlayerMovement.high_scores[1]);
			GUI.Label(new Rect(400.0f, 510.0f, 100.0f, 50.0f), "3.  "+PlayerMovement.high_scores[2]);
			GUI.Label(new Rect(400.0f, 530.0f, 100.0f, 50.0f), "4.  "+PlayerMovement.high_scores[3]);
			GUI.Label(new Rect(400.0f, 550.0f, 100.0f, 50.0f), "5.  "+PlayerMovement.high_scores[4]);
			// col2
			GUI.Label(new Rect(525.0f, 470.0f, 100.0f, 50.0f), "6.  "+PlayerMovement.high_scores[5]);
			GUI.Label(new Rect(525.0f, 490.0f, 100.0f, 50.0f), "7.  "+PlayerMovement.high_scores[6]);
			GUI.Label(new Rect(525.0f, 510.0f, 100.0f, 50.0f), "8.  "+PlayerMovement.high_scores[7]);
			GUI.Label(new Rect(525.0f, 530.0f, 100.0f, 50.0f), "9.  "+PlayerMovement.high_scores[8]);
			GUI.Label(new Rect(525.0f, 550.0f, 100.0f, 50.0f), "10. "+PlayerMovement.high_scores[9]);
		}
	}
}
