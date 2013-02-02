using UnityEngine;
using System.Collections;

// Class calculates x/y coords of successive subimages within a spritesheet, caches them to an array and iterates through the array at the desired FPS

public class AnimatedSprite : MonoBehaviour {
	
	public	float				mAnimFPS = 60.0f;
	
	private	Material			mMaterial;
	private Vector2[]			mCoords;
	private	float				timeStep;
	private	float				imageCount = 0;
	
	// Use this for initialization
	void Start () {
		mMaterial = gameObject.renderer.material;
		mCoords = new Vector2[12];
		timeStep = mAnimFPS/60.0f;//Application.targetFrameRate;
		
		//calculate the x/y coords; assume the spritesheet is filled completely and evenly
		for(int i=0; i<12; i++)
		{
			if(i<4)
			{
				// first four images
				mCoords[i] = new Vector2(i*0.25f, 0.0f);
			}else if(i<8)
			{
				// next four images
				mCoords[i] = new Vector2((i-4)*0.25f, 0.33f);
			}else
			{
				mCoords[i] = new Vector2((i-8)*0.25f, 0.67f);
			}
		}
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}
	
	void FixedUpdate()
	{
		imageCount += timeStep;
		if(imageCount >= 12.0f)
			imageCount = imageCount-12.0f;
		//change texture coordinates for renderer
		mMaterial.mainTextureOffset = mCoords[Mathf.FloorToInt(imageCount)];
	}
}
