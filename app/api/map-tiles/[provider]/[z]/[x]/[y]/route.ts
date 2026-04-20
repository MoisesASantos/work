import { NextResponse } from "next/server"

type Params = {
  provider: string
  z: string
  x: string
  y: string
}

const TILE_CONFIG = {
  osm: {
    buildUrl: ({ z, x, y }: Omit<Params, "provider">) => {
      const cleanY = y.endsWith(".png") ? y : `${y}.png`
      return `https://tile.openstreetmap.org/${z}/${x}/${cleanY}`
    },
  },
  esri: {
    buildUrl: ({ z, x, y }: Omit<Params, "provider">) => {
      const cleanY = y.replace(".png", "")
      return `https://server.arcgisonline.com/ArcGIS/rest/services/World_Imagery/MapServer/tile/${z}/${cleanY}/${x}`
    },
  },
} as const

export async function GET(
  _request: Request,
  context: { params: Promise<Params> }
) {
  const { provider, z, x, y } = await context.params

  if (!(provider in TILE_CONFIG)) {
    return new NextResponse("Unsupported map provider", { status: 400 })
  }

  const targetUrl = TILE_CONFIG[provider as keyof typeof TILE_CONFIG].buildUrl({ z, x, y })

  try {
    const upstream = await fetch(targetUrl, {
      headers: {
        "User-Agent": "ApothecaryMapProxy/1.0",
      },
      next: { revalidate: 86400 },
    })

    if (!upstream.ok) {
      return new NextResponse("Tile unavailable", { status: upstream.status })
    }

    const contentType = upstream.headers.get("content-type") || "image/png"
    const arrayBuffer = await upstream.arrayBuffer()

    return new NextResponse(arrayBuffer, {
      status: 200,
      headers: {
        "Content-Type": contentType,
        "Cache-Control": "public, max-age=86400, s-maxage=86400, stale-while-revalidate=86400",
      },
    })
  } catch {
    return new NextResponse("Tile fetch failed", { status: 502 })
  }
}
